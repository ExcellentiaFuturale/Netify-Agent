// Netify Agent
// Copyright (C) 2015-2022 eGloo Incorporated <http://www.egloo.ca>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iomanip>
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <vector>
#include <locale>
#include <atomic>
#include <regex>
#include <mutex>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/resource.h>

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <syslog.h>
#include <fcntl.h>
#include <dlfcn.h>

#include <arpa/inet.h>
#include <arpa/nameser.h>

#include <netdb.h>
#include <netinet/in.h>

#include <net/if.h>
#include <net/if_arp.h>
#if defined(__linux__)
#include <linux/if_packet.h>
#elif defined(__FreeBSD__)
#include <net/if_dl.h>
#endif

#define __FAVOR_BSD 1
#include <netinet/tcp.h>
#undef __FAVOR_BSD

#include <curl/curl.h>
#include <pcap/pcap.h>
#include <pthread.h>
#include <resolv.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#ifdef _ND_USE_CONNTRACK
#include <libnetfilter_conntrack/libnetfilter_conntrack.h>
#endif

#if defined(_ND_USE_LIBTCMALLOC) && defined(HAVE_GPERFTOOLS_MALLOC_EXTENSION_H)
#include <gperftools/malloc_extension.h>
#elif defined(HAVE_MALLOC_TRIM)
#include <malloc.h>
#endif

#include <radix/radix_tree.hpp>

using namespace std;

#include "netifyd.h"

#include "nd-config.h"
#include "nd-signal.h"
#include "nd-ndpi.h"
#include "nd-risks.h"
#include "nd-serializer.h"
#include "nd-packet.h"
#include "nd-json.h"
#include "nd-util.h"
#include "nd-addr.h"
#ifdef _ND_USE_NETLINK
#include "nd-netlink.h"
#endif
#include "nd-apps.h"
#include "nd-protos.h"
#include "nd-category.h"
#include "nd-flow.h"
#include "nd-flow-map.h"
#include "nd-dhc.h"
#include "nd-fhc.h"
#include "nd-thread.h"
class ndInstanceStatus;
#include "nd-plugin.h"
#include "nd-instance.h"
#include "nd-flow-parser.h"
#ifdef _ND_USE_CONNTRACK
#include "nd-conntrack.h"
#endif
#include "nd-detection.h"
#include "nd-capture.h"
#ifdef _ND_USE_LIBPCAP
#include "nd-capture-pcap.h"
#endif
#ifdef _ND_USE_TPACKETV3
#include "nd-capture-tpv3.h"
#endif
#ifdef _ND_USE_NFQUEUE
#include "nd-capture-nfq.h"
#endif
#include "nd-base64.h"
#include "nd-napi.h"

//#define _ND_LOG_PLUGIN_DEBUG    1

const map<ndPlugin::Type, string> ndPlugin::types = {
    // XXX: Keep in sync with Type enum
    make_pair(ndPlugin::TYPE_PROC, "processor"),
    make_pair(ndPlugin::TYPE_SINK, "sink"),
};

ndPlugin::ndPlugin(
    Type type,
    const string &tag, const Params &params)
    : ndThread(tag, -1), type(type)
{
    for (auto &param : params) {
        if (param.first == "conf_filename")
            conf_filename = param.second;
    }
#ifdef _ND_LOG_PLUGIN_DEBUG
    nd_dprintf("Plugin created: %s\n", tag.c_str());
#endif
}

ndPlugin::~ndPlugin()
{
#ifdef _ND_LOG_PLUGIN_DEBUG
    nd_dprintf("Plugin destroyed: %s\n", tag.c_str());
#endif
}

ndPluginSink::ndPluginSink(
    const string &tag, const ndPlugin::Params &params)
    : ndPlugin(ndPlugin::TYPE_SINK, tag, params),
    plq_size(0), plq_size_max(_ND_PLQ_DEFAULT_MAX_SIZE)
{
    int rc;

    pthread_condattr_t cond_attr;
    pthread_condattr_init(&cond_attr);

    pthread_condattr_setclock(&cond_attr, CLOCK_MONOTONIC);

    if ((rc = pthread_cond_init(&plq_cond, &cond_attr)) != 0)
        throw ndPluginException("pthread_cond_init", strerror(rc));

    pthread_condattr_destroy(&cond_attr);

    if ((rc = pthread_mutex_init(&plq_cond_mutex, NULL)) != 0)
        throw ndPluginException("pthread_mutex_init", strerror(rc));

#ifdef _ND_LOG_PLUGIN_DEBUG
    nd_dprintf("Sink plugin created: %s\n", tag.c_str());
#endif
}

ndPluginSink::~ndPluginSink()
{
    pthread_cond_destroy(&plq_cond);
    pthread_mutex_destroy(&plq_cond_mutex);
#ifdef _ND_LOG_PLUGIN_DEBUG
    nd_dprintf("Sink plugin destroyed: %s\n", tag.c_str());
#endif
}

ndPluginSinkPayload *ndPluginSinkPayload::Create(
    size_t length, const uint8_t *data,
    const ndPlugin::Channels &channels, uint8_t flags)
{
    ndPluginSinkPayload *p = nullptr;

    if (! (flags & ndPlugin::DF_GZ_DEFLATE))
        p = new ndPluginSinkPayload(length, data, channels, flags);
    else {
        vector<uint8_t> buffer;
        nd_gz_deflate(length, data, buffer);
        p = new ndPluginSinkPayload(
            buffer.size(), &buffer[0], channels, flags
        );
    }

    if (p == nullptr) {
        throw ndSystemException(__PRETTY_FUNCTION__,
            "new sink payload", ENOMEM
        );
    }

    return p;
}

void ndPluginSink::QueuePayload(ndPluginSinkPayload *payload)
{
    Lock();

    plq_public.push(payload);

    Unlock();

    int rc;

    if ((rc = pthread_cond_broadcast(&plq_cond)) != 0) {
        throw ndPluginException(
            "pthread_cond_broadcast", strerror(rc)
        );
    }
}

size_t ndPluginSink::PullPayloadQueue(void)
{
    if (plq_public.size() == 0)
        return 0;

    ndPluginSinkPayload *p;

    do {
        while (plq_private.size() && plq_size > plq_size_max) {
            p = plq_private.front();
            plq_private.pop();

            plq_size -= p->length;
            delete p;
        }

        p = plq_public.front();
        plq_public.pop();

        plq_size += p->length;
        plq_private.push(p);
    }
    while (plq_public.size() > 0);

    return plq_private.size();
}

size_t ndPluginSink::WaitOnPayloadQueue(unsigned timeout)
{
    Lock();

    size_t entries = PullPayloadQueue();

    if (timeout > 0 && entries == 0) {

        Unlock();

        int rc;
        if ((rc = pthread_mutex_lock(&plq_cond_mutex)) != 0) {
            throw ndPluginException(
                "pthread_mutex_lock", strerror(rc)
            );
        }

        struct timespec ts_cond;
        if (clock_gettime(CLOCK_MONOTONIC, &ts_cond) != 0) {
            throw ndPluginException(
                "clock_gettime", strerror(errno)
            );
        }

        ts_cond.tv_sec += timeout;

        if ((rc = pthread_cond_timedwait(
            &plq_cond, &plq_cond_mutex, &ts_cond)) != 0 &&
            rc != ETIMEDOUT) {
            throw ndPluginException(
                "pthread_cond_timedwait", strerror(rc)
            );
        }

        if ((rc = pthread_mutex_unlock(&plq_cond_mutex)) != 0) {
            throw ndPluginException(
                "pthread_mutex_unlock", strerror(rc));
        }

        Lock();

        entries = PullPayloadQueue();
    }

    Unlock();

    return entries;
}

ndPluginProcessor::ndPluginProcessor(
    const string &tag, const ndPlugin::Params &params)
    : ndPlugin(ndPlugin::TYPE_PROC, tag, params)
{
#if 0
    for (auto &param : params) {
        if (param.first == "sink_targets") {
            stringstream ss(param.second);

            while (ss.good()) {
                string value;
                getline(ss, value, ',');

                nd_trim(value, ' ');

                if (value.empty()) continue;

                string target;
                string channel = "default";

                size_t p = value.find_first_of(":");

                if (p == string::npos)
                    target = value;
                else {
                    target = value.substr(0, p);
                    channel = value.substr(p + 1);
                }

                auto i = sink_targets.find(target);

                if (i != sink_targets.end()) {
                    if (! i->second.insert(channel).second) {
                        throw ndPluginException(
                            "duplicate channel specified",
                            channel
                        );
                    }
                }
                else {
                    ndPlugin::Channels channels = { channel };

                    if (! sink_targets.insert(
                        make_pair(target, channels)).second) {
                        throw ndPluginException(
                            "error creating target",
                            target
                        );
                    }
                }
            }
        }
    }
#endif
#ifdef _ND_LOG_PLUGIN_DEBUG
    nd_dprintf("Processor plugin created: %s\n", tag.c_str());
#endif
}

ndPluginProcessor::~ndPluginProcessor()
{
#ifdef _ND_LOG_PLUGIN_DEBUG
    nd_dprintf("Processor plugin destroyed: %s\n", tag.c_str());
#endif
}

void ndPluginProcessor::DispatchSinkPayload(
    const string &target, const ndPlugin::Channels &channels,
    size_t length, const uint8_t *payload, uint8_t flags)
{
    ndInstance& ndi = ndInstance::GetInstance();

    ndPluginSinkPayload *sp = ndPluginSinkPayload::Create(
        length, payload, channels, flags
    );

    if (ndi.plugins.DispatchSinkPayload(target, sp))
        return;

    throw ndPluginException(
        "sink target not found", target.c_str()
    );
}

void ndPluginProcessor::DispatchSinkPayload(
    const string &target, const ndPlugin::Channels &channels,
    const json &j, uint8_t flags)
{
    if ((flags & ndPlugin::DF_FORMAT_MSGPACK)) {
        vector<uint8_t> output;
        output = json::to_msgpack(j);

        if ((flags & ndPlugin::DF_ADD_HEADER)) {
            json jheader;
            jheader["length"] = output.size();

            vector<uint8_t> header;
            header = json::to_msgpack(jheader);

            DispatchSinkPayload(
                target, channels, header, flags
            );
        }

        DispatchSinkPayload(
            target, channels, output, flags
        );
    }
    else {
        string output;
        nd_json_to_string(j, output, ndGC_DEBUG);

        flags |= ndPlugin::DF_FORMAT_JSON;

        if ((flags & ndPlugin::DF_ADD_HEADER)) {
            output.append("\n");

            json jheader;
            jheader["length"] = output.size();

            string header;
            nd_json_to_string(jheader, header, ndGC_DEBUG);
            header.append("\n");

            DispatchSinkPayload(
                target, channels, header.size(),
                (const uint8_t *)header.c_str(), flags
            );
        }

        DispatchSinkPayload(
            target, channels,
            output.size(), (const uint8_t *)output.c_str(), flags
        );
    }
}

ndPluginLoader::ndPluginLoader(
    const string &tag,
    const string &so_name, const ndPlugin::Params &params)
    : tag(tag), so_name(so_name), so_handle(NULL)
{
    so_handle = dlopen(so_name.c_str(), RTLD_NOW);
    if (so_handle == NULL)
        throw ndPluginException(tag, dlerror());

    char *dlerror_string;
    ndPlugin *(*ndPluginInit)(const string &, const ndPlugin::Params &);

    dlerror();
    *(void **) (&ndPluginInit) = dlsym(so_handle, "ndPluginInit");

    if ((dlerror_string = dlerror()) != NULL) {
        dlclose(so_handle);
        so_handle = NULL;
        throw ndPluginException(tag, dlerror_string);
    }

    plugin = (*ndPluginInit)(tag, params);
    if (plugin == NULL) {
        dlclose(so_handle);
        so_handle = NULL;
        throw ndPluginException(tag, "ndPluginInit");
    }

    nd_dprintf("Plugin loaded: %s: %s\n",
        tag.c_str(), so_name.c_str()
    );
}

ndPluginLoader::~ndPluginLoader()
{
    if (so_handle != NULL) {
        dlclose(so_handle);
#ifdef _ND_LOG_PLUGIN_DEBUG
        nd_dprintf("Plugin dereferenced: %s: %s\n",
            tag.c_str(), so_name.c_str()
        );
#endif
    }
}

void ndPluginManager::Load(ndPlugin::Type type, bool create)
{
    lock_guard<mutex> ul(lock);

    for (auto &t : ndPlugin::types) {
        if (type != ndPlugin::TYPE_BASE && type != t.first)
            continue;

        const ndGlobalConfig::map_plugin *plugins = nullptr;

        switch (t.first) {
        case ndPlugin::TYPE_PROC:
            plugins = &ndGC.plugin_processors;
            break;
        case ndPlugin::TYPE_SINK:
            plugins = &ndGC.plugin_sinks;
            break;
        default:
            break;
        }

        if (plugins == nullptr) continue;

        for (auto &i : *plugins) {
            ndPluginLoader *loader = nullptr;

            loader = new ndPluginLoader(
                i.first, i.second.first, i.second.second);

            if (loader->GetPlugin()->GetType() != t.first)
                throw ndPluginException(i.first, "wrong type");

            if (create)
                loader->GetPlugin()->Create();

            map_plugin *mp = nullptr;

            switch (t.first) {
            case ndPlugin::TYPE_PROC:
                mp = &processors;
                break;
            case ndPlugin::TYPE_SINK:
                mp = &sinks;
                break;
            default:
                throw ndPluginException(
                    i.first, "invalid type"
                );
                break;
            }

            auto pl = mp->find(t.second);

            if (pl != mp->end()) {
                throw ndPluginException(i.first,
                    "duplicate plugin tag"
                );
            }

            if (! mp->insert(make_pair(i.first, loader)).second) {
                throw ndPluginException(i.first,
                    "failed to insert loader"
                );
            }
        }
    }
}

bool ndPluginManager::Create(ndPlugin::Type type)
{
    lock_guard<mutex> ul(lock);

    for (auto &t : ndPlugin::types) {
        if (type != ndPlugin::TYPE_BASE && type != t.first)
            continue;

        map_plugin *mp = nullptr;

        switch (t.first) {
        case ndPlugin::TYPE_PROC:
            mp = &processors;
            break;
        case ndPlugin::TYPE_SINK:
            mp = &sinks;
            break;
        default:
            throw ndPluginException(
                t.second, "invalid type"
            );
            break;
        }

        auto pl = mp->find(t.second);

        if (pl == mp->end()) {
            throw ndPluginException(t.second,
                "plugin not found"
            );
        }

        pl->second->GetPlugin()->Create();

        return true;
    }

    return false;
}

size_t ndPluginManager::Terminate(ndPlugin::Type type)
{
    size_t count = 0;

    if (type == ndPlugin::TYPE_BASE ||
        type == ndPlugin::TYPE_PROC) {
        for (auto &p : processors) {
            count++;
            p.second->GetPlugin()->Terminate();
        }
    }

    if (type == ndPlugin::TYPE_BASE ||
        type == ndPlugin::TYPE_SINK) {
        for (auto &p : sinks) {
            count++;
            p.second->GetPlugin()->Terminate();
        }
    }

    return count;
}

void ndPluginManager::Destroy(ndPlugin::Type type)
{
    lock_guard<mutex> ul(lock);

    if (type == ndPlugin::TYPE_BASE ||
        type == ndPlugin::TYPE_PROC) {
        for (auto &p : processors)
            p.second->GetPlugin()->Terminate();

        for (auto &p : processors) {
            delete p.second->GetPlugin();
            delete p.second;
        }

        processors.clear();
    }

    if (type == ndPlugin::TYPE_BASE ||
        type == ndPlugin::TYPE_SINK) {
        for (auto &p : sinks)
            p.second->GetPlugin()->Terminate();

        for (auto &p : sinks) {
            delete p.second->GetPlugin();
            delete p.second;
        }

        sinks.clear();
    }
}

size_t ndPluginManager::Reap(ndPlugin::Type type)
{
    size_t count = 0;

    for (auto &t : ndPlugin::types) {
        if (type != ndPlugin::TYPE_BASE && type != t.first)
            continue;

        map_plugin *mp = nullptr;

        switch (t.first) {
        case ndPlugin::TYPE_PROC:
            mp = &processors;
            break;
        case ndPlugin::TYPE_SINK:
            mp = &sinks;
            break;
        default:
            throw ndPluginException(
                t.second, "invalid type"
            );
            break;
        }

        for (map_plugin::iterator p = mp->begin();
            p != mp->end(); ) {

            if (! p->second->GetPlugin()->HasTerminated()) {
                p++;
                continue;
            }

            nd_printf("Plugin has terminated: %s: %s\n",
                p->second->GetTag().c_str(),
                p->second->GetObjectName().c_str()
            );

            lock_guard<mutex> ul(lock);

            delete p->second->GetPlugin();
            delete p->second;

            count++;
            p = mp->erase(p);
        }
    }

    return count;
}

void ndPluginManager::BroadcastEvent(ndPlugin::Type type,
    ndPlugin::Event event, void *param)
{
    lock_guard<mutex> ul(lock);

    for (auto &t : ndPlugin::types) {
        if (type != ndPlugin::TYPE_BASE && type != t.first)
            continue;

        map_plugin *mp = nullptr;

        switch (t.first) {
        case ndPlugin::TYPE_PROC:
            mp = &processors;
            break;
        case ndPlugin::TYPE_SINK:
            mp = &sinks;
            break;
        default:
            throw ndPluginException(
                t.second, "invalid type"
            );
            break;
        }

        for (auto &p : *mp)
            p.second->GetPlugin()->DispatchEvent(event, param);
    }
}

void ndPluginManager::BroadcastSinkPayload(
    ndPluginSinkPayload *payload)
{
    lock_guard<mutex> ul(lock);

    if (sinks.empty()) {
        delete payload;
        return;
    }

    auto p = sinks.cbegin();

    for ( ; p != prev(sinks.cend()); p++) {
        ndPluginSinkPayload *sp = ndPluginSinkPayload::Create(
            payload
        );

        reinterpret_cast<ndPluginSink *>(
            p->second->GetPlugin())->QueuePayload(sp);
    }

    reinterpret_cast<ndPluginSink *>(
        p->second->GetPlugin())->QueuePayload(payload);
}

bool ndPluginManager::DispatchSinkPayload(const string &target,
    ndPluginSinkPayload *payload)
{
    lock_guard<mutex> ul(lock);

    auto p = sinks.find(target);

    if (p == sinks.end()) return false;

    reinterpret_cast<ndPluginSink *>(
        (*p).second->GetPlugin())->QueuePayload(payload);

    return true;
}

void ndPluginManager::BroadcastProcessorEvent(
    ndPluginProcessor::Event event, ndFlowMap *flow_map)
{
    lock_guard<mutex> ul(lock);

    for (auto &p : processors) {
        reinterpret_cast<ndPluginProcessor *>(
            p.second->GetPlugin())->DispatchProcessorEvent(
                event, flow_map
            );
    }
}

void ndPluginManager::BroadcastProcessorEvent(
    ndPluginProcessor::Event event, nd_flow_ptr& flow)
{
    lock_guard<mutex> ul(lock);

    for (auto &p : processors) {
        reinterpret_cast<ndPluginProcessor *>(
            p.second->GetPlugin())->DispatchProcessorEvent(
                event, flow
            );
    }
}

void ndPluginManager::BroadcastProcessorEvent(
    ndPluginProcessor::Event event, ndInterfaces *interfaces)
{
    lock_guard<mutex> ul(lock);

    for (auto &p : processors) {
        reinterpret_cast<ndPluginProcessor *>(
            p.second->GetPlugin())->DispatchProcessorEvent(
                event, interfaces
            );
    }
}

void ndPluginManager::BroadcastProcessorEvent(
    ndPluginProcessor::Event event,
    const string &iface, ndPacketStats *stats)
{
    lock_guard<mutex> ul(lock);

    for (auto &p : processors) {
        reinterpret_cast<ndPluginProcessor *>(
            p.second->GetPlugin())->DispatchProcessorEvent(
                event, iface, stats
            );
    }
}

void ndPluginManager::BroadcastProcessorEvent(
    ndPluginProcessor::Event event, ndPacketStats *stats)
{
    lock_guard<mutex> ul(lock);

    for (auto &p : processors) {
        reinterpret_cast<ndPluginProcessor *>(
            p.second->GetPlugin())->DispatchProcessorEvent(
                event, stats
            );
    }
}

void ndPluginManager::BroadcastProcessorEvent(
    ndPluginProcessor::Event event, ndInstanceStatus *status)
{
    lock_guard<mutex> ul(lock);

    for (auto &p : processors) {
        reinterpret_cast<ndPluginProcessor *>(
            p.second->GetPlugin())->DispatchProcessorEvent(
                event, status
            );
    }
}

void ndPluginManager::BroadcastProcessorEvent(
    ndPluginProcessor::Event event)
{
    lock_guard<mutex> ul(lock);

    for (auto &p : processors) {
        reinterpret_cast<ndPluginProcessor *>(
            p.second->GetPlugin())->DispatchProcessorEvent(
                event
            );
    }
}

void ndPluginManager::DumpVersions(ndPlugin::Type type)
{
    for (auto &t : ndPlugin::types) {
        if (type != ndPlugin::TYPE_BASE && type != t.first)
            continue;

        map_plugin *mp = nullptr;

        switch (t.first) {
        case ndPlugin::TYPE_PROC:
            mp = &processors;
            break;
        case ndPlugin::TYPE_SINK:
            mp = &sinks;
            break;
        default:
            throw ndPluginException(
                t.second, "invalid type"
            );
            break;
        }

        lock_guard<mutex> ul(lock);

        for (auto &p : *mp) {
            string version;
            p.second->GetPlugin()->GetVersion(version);

            fprintf(stderr, "%16s: %s: v%s\n",
                p.second->GetTag().c_str(),
                p.second->GetObjectName().c_str(),
                (version.empty()) ? "?.?.?" : version.c_str()
            );
        }
    }
}

// vi: expandtab shiftwidth=4 softtabstop=4 tabstop=4
