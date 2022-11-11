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

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <deque>
#include <vector>
#include <map>
#include <regex>
#include <mutex>

#include <sys/inotify.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std;

#include "netifyd.h"

#include "nd-ndpi.h"
#include "nd-sha1.h"
#include "nd-json.h"
#include "nd-util.h"
#include "nd-inotify.h"

ndInotify::ndInotify()
{
    int flags;

    if ((fd = inotify_init1(IN_NONBLOCK | IN_CLOEXEC)) < 0)
        throw ndInotifyException(strerror(errno));

    if (fcntl(fd, F_SETOWN, getpid()) < 0)
        throw ndInotifyException(strerror(errno));

    if (fcntl(fd, F_SETSIG, SIGIO) < 0)
        throw ndInotifyException(strerror(errno));

    flags = fcntl(fd, F_GETFL);
    if (fcntl(fd, F_SETFL, flags | O_ASYNC | O_NONBLOCK) < 0)
        throw ndInotifyException(strerror(errno));
}

ndInotify::~ndInotify()
{
    for (nd_inotify_map::iterator i = inotify_watch.begin();
        i != inotify_watch.end(); i++) {
        inotify_rm_watch(fd, i->second->wd);
        delete i->second;
    }

    if (fd > -1)
        close(fd);
}

void ndInotify::AddWatch(const string &tag, const string &filename)
{
    if (inotify_watch.find(tag) == inotify_watch.end()) {
        struct nd_inotify_watch *watch = new struct nd_inotify_watch;

        if (watch == NULL)
            throw ndInotifyException(strerror(ENOMEM));

        memset(watch, 0, sizeof(struct nd_inotify_watch));
        watch->wd = -1;
        watch->filename = filename.c_str();

        inotify_watch[tag] = watch;
    }
}

void ndInotify::RefreshWatches(void)
{
    for (nd_inotify_map::iterator i = inotify_watch.begin();
        i != inotify_watch.end(); i++) {

        if (i->second->wd >= 0) continue;

        i->second->wd = inotify_add_watch(
            fd, i->second->filename,
            IN_DELETE_SELF | IN_CLOSE_WRITE | IN_MODIFY);

        if (i->second->wd < 0) {
            nd_dprintf("Error creating inotify watch: %s: %s\n",
                i->first.c_str(), strerror(errno));
        }
        else
            i->second->event_occured = true;
    }
}

void ndInotify::ProcessEvent(void)
{
    ssize_t bytes;
    uint8_t buffer[ND_INOTIFY_BUFSIZ];
    uint8_t *p = buffer;

    do {
        bytes = read(fd, buffer, ND_INOTIFY_BUFSIZ);

        if (bytes > 0) {
            struct inotify_event *iev = (struct inotify_event *)p;
            while (bytes > 0) {

                nd_inotify_map::iterator watch;
                for (watch = inotify_watch.begin();
                    watch != inotify_watch.end(); watch++) {
                    if (iev->wd != watch->second->wd) continue;
                    break;
                }

                if (watch != inotify_watch.end()) {
                    if (watch->second->event_occured == false &&
                        ((iev->mask & IN_DELETE_SELF) ||
                        (iev->mask & IN_MODIFY) || (iev->mask & IN_CLOSE_WRITE))) {

                        nd_dprintf("File event occured: %s [%s]\n",
                            watch->first.c_str(),
                            (iev->mask & IN_DELETE_SELF) ? "DELETE_SELF" :
                            (iev->mask & IN_MODIFY) ? "MODIFY" :
                            (iev->mask & IN_CLOSE_WRITE) ?
                                "CLOSE_WRITE" : "IGNORE");

                        if (iev->mask & IN_DELETE_SELF) {
                            inotify_rm_watch(fd, watch->second->wd);
                            watch->second->wd = -1;
                        }

                        watch->second->event_occured = true;
                        watch->second->rehash = true;
                    }
                }

                p += sizeof(struct inotify_event) + iev->len;
                bytes -= sizeof(struct inotify_event) + iev->len;
                iev = (struct inotify_event *)p;
            }
        }
        else if (bytes < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) break;
            throw ndInotifyException(strerror(errno));
        }
    }
    while (bytes != 0);

    for (nd_inotify_map::iterator i = inotify_watch.begin();
        i != inotify_watch.end(); i++) {

        if (i->second->rehash == false) continue;

        uint8_t digest[SHA1_DIGEST_LENGTH];

        if (nd_sha1_file(i->second->filename, digest) < 0)
            continue;

        if (i->second->digest == NULL) {
            i->second->digest = new uint8_t[SHA1_DIGEST_LENGTH];
            memcpy(i->second->digest, digest, SHA1_DIGEST_LENGTH);
        }
        else {
            if (memcmp(i->second->digest, digest, SHA1_DIGEST_LENGTH))
                memcpy(i->second->digest, digest, SHA1_DIGEST_LENGTH);
            else
                i->second->event_occured = false;
        }

        i->second->rehash = false;
    }
}

bool ndInotify::EventOccured(const string &tag)
{
    nd_inotify_map::const_iterator i = inotify_watch.find(tag);

    if (i == inotify_watch.end()) return false;

    if (i->second->event_occured) {
        i->second->event_occured = false;
        return true;
    }

    return false;
}

// vi: expandtab shiftwidth=4 softtabstop=4 tabstop=4
