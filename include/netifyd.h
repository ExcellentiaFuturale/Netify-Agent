// Netify Agent
// Copyright (C) 2015-2018 eGloo Incorporated <http://www.egloo.ca>
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

#ifndef _ND_H
#define _ND_H

#ifndef ETH_ALEN
#include <net/ethernet.h>
#if !defined(ETH_ALEN) && defined(ETHER_ADDR_LEN)
#define ETH_ALEN ETHER_ADDR_LEN
#endif
#endif
#ifndef ETH_ALEN
#error Unable to define ETH_ALEN.
#endif

#ifdef _ND_USE_NETLINK
#include <linux/netlink.h>
#endif

#ifndef CLOCK_MONOTONIC_RAW
#define CLOCK_MONOTONIC_RAW CLOCK_MONOTONIC
#endif

#ifndef s6_addr32
#define s6_addr32 __u6_addr.__u6_addr32
#endif

#include <limits.h>
#ifndef HOST_NAME_MAX
#ifdef _POSIX_HOST_NAME_MAX
#define HOST_NAME_MAX _POSIX_HOST_NAME_MAX
#else
#error Unable to define HOST_NAME_MAX.
#endif
#endif

#define ND_STATS_INTERVAL       15      // Collect stats every N seconds
#define ND_MAX_BACKLOG_KB       2048    // Maximum upload queue size in kB
#define ND_DETECTION_TICKS      1000    // Ticks-per-second (1000 = milliseconds)
#define ND_IDLE_SCAN_TIME       10      // Idle flow scan in milliseconds
#define ND_IDLE_FLOW_TIME       30000   // Purge idle flows older than this (30s)
#define ND_IDLE_DNS_CACHE_TTL  (60 * 30)// Purge TTL for idle DNS cache entries.
#define ND_HASH_BUCKETS_FLOWS   1613    // Initial flows map bucket count.
#define ND_HASH_BUCKETS_DNSARS  1613    // DNS cache address record hash buckets.

#define ND_MAX_TCP_PKTS         10      // Maximum number of TCP packets to process.
#define ND_MAX_UDP_PKTS         8       // Maximum number of UDP packets to process.

#ifndef ND_VOLATILE_STATEDIR
#define ND_VOLATILE_STATEDIR    "/var/run/netifyd"
#endif

#ifndef ND_PERSISTENT_STATEDIR
#define ND_PERSISTENT_STATEDIR  "/etc/netify.d"
#endif

#ifndef ND_DATADIR
#define ND_DATADIR              "/usr/share/netifyd"
#endif

#ifndef ND_CONF_FILE_NAME
#define ND_CONF_FILE_NAME       "/etc/netifyd.conf"
#endif

#ifndef ND_PID_FILE_NAME
#define ND_PID_FILE_NAME        ND_VOLATILE_STATEDIR "/netifyd.pid"
#endif

#define ND_DNS_CACHE_FILE_NAME  ND_VOLATILE_STATEDIR "/dns-cache.csv"

#define ND_JSON_VERSION         1.6     // JSON format version
#ifndef ND_JSON_FILE_NAME
#define ND_JSON_FILE_NAME       ND_VOLATILE_STATEDIR "/netifyd.json"
#endif
#define ND_JSON_FILE_USER       "root"
#define ND_JSON_FILE_GROUP      "webconfig"
#define ND_JSON_FILE_MODE       0640
#define ND_JSON_FILE_RESPONSE   ND_VOLATILE_STATEDIR "/netifyd-response.json"
#define ND_JSON_FILE_BAD_SEND   ND_VOLATILE_STATEDIR "/netifyd-bad-send.json"
#define ND_JSON_FILE_BAD_RECV   ND_VOLATILE_STATEDIR "/netifyd-bad-recv.json"
#define ND_JSON_DATA_CHUNKSIZ   4096

#define ND_PCAP_SNAPLEN         1536    // Capture snap length
#define ND_PCAP_READ_TIMEOUT    500     // Milliseconds

#define ND_URL_UPLOAD           "https://sink.netify.ai/v2/"
#define ND_URL_PROVISION        "https://portal.netify.ai/app/provision/agent?uuid="
#define ND_COOKIE_JAR           ND_VOLATILE_STATEDIR "/netifyd.cookies"
#define ND_UPLOAD_TIMEOUT       300     // Default 5-minute upload timeout

#define ND_AGENT_UUID_PATH      ND_PERSISTENT_STATEDIR "/agent.uuid"
#define ND_AGENT_UUID_NULL      "00-00-00-00"
#define ND_AGENT_UUID_LEN       11

#define ND_AGENT_SERIAL_NULL    "-"

#define ND_SITE_UUID_PATH       ND_PERSISTENT_STATEDIR "/site.uuid"
#define ND_SITE_UUID_NULL       "-"
#define ND_SITE_UUID_LEN        36

#define ND_ETHERS_FILE_NAME     "/etc/ethers"

#ifdef _ND_USE_WATCHDOGS
#define ND_WD_UPLOAD            ND_VOLATILE_STATEDIR "/upload.wd"
#endif

// Compress data if it's over this size (bytes)
#define ND_COMPRESS_SIZE       (1024 * 10)
#define ND_ZLIB_CHUNK_SIZE      16384   // Compress this many bytes at a time

#define ND_SOCKET_PORT          "7150"
#define ND_SOCKET_PATH_MODE     0640
#define ND_SOCKET_PATH_USER     "root"
#define ND_SOCKET_PATH_GROUP    "root"

#ifndef PACKAGE_URL
#define PACKAGE_URL             "http://www.egloo.ca/"
#endif

#define ND_CONF_SINK_BASE       "netify-sink.conf"
#define ND_CONF_SINK_PATH       ND_PERSISTENT_STATEDIR "/" ND_CONF_SINK_BASE

#define ND_STR_ETHALEN          (ETH_ALEN * 2 + ETH_ALEN - 1)

#include "nd-sha1.h"

typedef unordered_map<string, vector<string> > nd_device_addrs;
typedef map<string, nd_device_addrs *> nd_devices;
typedef unordered_map<string, string> nd_device_ethers;
typedef vector<pair<bool, string> > nd_ifaces;
typedef vector<pair<string, string> > nd_device_addr;
typedef map<string, string> nd_device_filter;
typedef map<string, string> nd_device_netlink;
typedef map<string, string> nd_inotify_watch;
#ifdef _ND_USE_PLUGINS
class ndPluginLoader;
typedef map<string, ndPluginLoader *> nd_plugins;
#endif

enum nd_global_flags {
    ndGF_DEBUG = 0x1,
    ndGF_DEBUG_UPLOAD = 0x2,
    ndGF_DEBUG_WITH_ETHERS = 0x4,
    ndGF_DEBUG_DNS_CACHE = 0x8,
    ndGF_OVERRIDE_SINK_CONFIG = 0x10,
    ndGF_BITHOLE_0x20 = 0x20,
    ndGF_BITHOLE_0x40 = 0x40,
    ndGF_SSL_USE_TLSv1 = 0x80,
    ndGF_SSL_VERIFY = 0x100,
    ndGF_USE_CONNTRACK = 0x200,
    ndGF_USE_NETLINK = 0x400,
    ndGF_FREE_0x800 = 0x800,
    ndGF_USE_SINK = 0x1000,
    ndGF_USE_DNS_CACHE = 0x2000,
    ndGF_DNS_CACHE_SAVE = 0x4000,
    ndGF_JSON_SAVE = 0x8000,
    ndGF_VERBOSE = 0x10000,
    ndGF_REPLAY_DELAY = 0x20000,
    ndGF_REMAIN_IN_FOREGROUND = 0x40000,
};

#define ND_DEBUG (nd_config.flags & ndGF_DEBUG)
#define ND_DEBUG_UPLOAD (nd_config.flags & ndGF_DEBUG_UPLOAD)
#define ND_DEBUG_WITH_ETHERS (nd_config.flags & ndGF_DEBUG_WITH_ETHERS)
#define ND_DEBUG_DNS_CACHE (nd_config.flags & ndGF_DEBUG_DNS_CACHE)
#define ND_OVERRIDE_SINK_CONFIG (nd_config.flags & ndGF_OVERRIDE_SINK_CONFIG)
#define ND_SSL_USE_TLSv1 (nd_config.flags & ndGF_SSL_USE_TLSv1)
#define ND_SSL_VERIFY (nd_config.flags & ndGF_SSL_VERIFY)
#define ND_USE_CONNTRACK (nd_config.flags & ndGF_USE_CONNTRACK)
#define ND_USE_NETLINK (nd_config.flags & ndGF_USE_NETLINK)
#define ND_USE_SINK (nd_config.flags & ndGF_USE_SINK)
#define ND_USE_DNS_CACHE (nd_config.flags & ndGF_USE_DNS_CACHE)
#define ND_DNS_CACHE_SAVE (nd_config.flags & ndGF_DNS_CACHE_SAVE)
#define ND_JSON_SAVE (nd_config.flags & ndGF_JSON_SAVE)
#define ND_VERBOSE (nd_config.flags & ndGF_VERBOSE)
#define ND_REPLAY_DELAY (nd_config.flags & ndGF_REPLAY_DELAY)
#define ND_REMAIN_IN_FOREGROUND (nd_config.flags & ndGF_REMAIN_IN_FOREGROUND)

#define ND_GF_SET_FLAG(flag, value) \
{ \
    if (value) nd_config.flags |= flag; \
    else nd_config.flags &= ~flag; \
}

typedef struct nd_global_config_t {
    char *path_config;
    char *path_sink_config;
    char *path_json;
    char *path_uuid;
    char *path_uuid_serial;
    char *path_uuid_site;
    char *url_upload;
    char *uuid;
    char *uuid_serial;
    char *uuid_site;
    size_t max_backlog;
    uint32_t flags;
    uint8_t digest_sink_config[SHA1_DIGEST_LENGTH];
    unsigned max_tcp_pkts;
    unsigned max_udp_pkts;
    unsigned update_interval;
    unsigned upload_timeout;
    unsigned dns_cache_ttl;

    vector<pair<string, string> > socket_host;
    vector<string> socket_path;
    vector<struct sockaddr *> privacy_filter_host;
    vector<uint8_t *> privacy_filter_mac;
    nd_device_filter device_filters;
#ifdef _ND_USE_PLUGINS
    map<string, string> services;
    map<string, string> tasks;
#endif
} nd_global_config;

typedef struct nd_agent_stats_t
{
    struct timespec ts_epoch;
    struct timespec ts_now;
    uint32_t flows;
    uint32_t flows_prev;
#if (SIZEOF_LONG == 4)
    uint32_t maxrss_kb;
    uint32_t maxrss_kb_prev;
#elif (SIZEOF_LONG == 8)
    uint64_t maxrss_kb;
    uint64_t maxrss_kb_prev;
#endif
#if defined(_ND_USE_LIBTCMALLOC) && defined(HAVE_GPERFTOOLS_MALLOC_EXTENSION_H)
    size_t tcm_alloc_kb;
    size_t tcm_alloc_kb_prev;
#endif
} nd_agent_stats;

typedef struct nd_packet_stats_t
{
    uint64_t pkt_raw;
    uint64_t pkt_eth;
    uint64_t pkt_mpls;
    uint64_t pkt_pppoe;
    uint64_t pkt_vlan;
    uint64_t pkt_frags;
    uint64_t pkt_discard;
    uint32_t pkt_maxlen;
    uint64_t pkt_ip;
    uint64_t pkt_ip4;
    uint64_t pkt_ip6;
    uint64_t pkt_icmp;
    uint64_t pkt_igmp;
    uint64_t pkt_tcp;
    uint64_t pkt_udp;
    uint64_t pkt_ip_bytes;
    uint64_t pkt_ip4_bytes;
    uint64_t pkt_ip6_bytes;
    uint64_t pkt_wire_bytes;
    uint64_t pkt_discard_bytes;

    inline nd_packet_stats_t& operator+=(const nd_packet_stats_t &rhs) {
        pkt_raw += rhs.pkt_raw;
        pkt_eth += rhs.pkt_eth;
        pkt_mpls += rhs.pkt_mpls;
        pkt_pppoe += rhs.pkt_pppoe;
        pkt_vlan += rhs.pkt_vlan;
        pkt_frags += rhs.pkt_frags;
        pkt_discard += rhs.pkt_discard;
        if (rhs.pkt_maxlen > pkt_maxlen)
            pkt_maxlen = rhs.pkt_maxlen;
        pkt_ip += rhs.pkt_ip;
        pkt_ip4 += rhs.pkt_ip4;
        pkt_ip6 += rhs.pkt_ip6;
        pkt_icmp += rhs.pkt_icmp;
        pkt_igmp += rhs.pkt_igmp;
        pkt_tcp += rhs.pkt_tcp;
        pkt_udp += rhs.pkt_udp;
        pkt_ip_bytes += rhs.pkt_ip_bytes;
        pkt_ip4_bytes += rhs.pkt_ip4_bytes;
        pkt_ip6_bytes += rhs.pkt_ip6_bytes;
        pkt_wire_bytes += rhs.pkt_wire_bytes;
        pkt_discard_bytes += rhs.pkt_discard_bytes;
        return *this;
    }
} nd_packet_stats;

typedef map<string, nd_packet_stats *> nd_stats;

typedef pair<time_t, string> nd_dns_tuple;
typedef unordered_map<string, nd_dns_tuple> nd_dns_ar;
typedef pair<nd_dns_ar::iterator, bool> nd_dns_cache_insert;
typedef pair<string, nd_dns_tuple> nd_dns_cache_insert_pair;

typedef struct nd_dns_cache_t
{
    pthread_mutex_t lock;
    nd_dns_ar map_ar;

    void insert(sa_family_t af, const uint8_t *addr, const string &hostname);
    void insert(const string &digest, const string &hostname);

    bool lookup(const struct in_addr &addr, string &hostname);
    bool lookup(const struct in6_addr &addr, string &hostname);
    bool lookup(const string &digest, string &hostname);

    size_t purge(void);

    void load(void);
    void save(void);
} nd_dns_cache;

void nd_json_agent_hello(string &json_string);
void nd_json_agent_status(string &json_string);
void nd_json_protocols(string &json_string);

class ndException : public runtime_error
{
public:
    explicit ndException(
        const string &where_arg, const string &what_arg) throw();
    virtual ~ndException() throw();

    virtual const char *what() const throw();

    string where_arg;
    string what_arg;
    const char *message;
};

class ndSystemException : public runtime_error
{
public:
    explicit ndSystemException(
        const string &where_arg, const string &what_arg, int why_arg) throw();
    virtual ~ndSystemException() throw();

    virtual const char *what() const throw();

    string where_arg;
    string what_arg;
    int why_arg;
    const char *message;
};

#endif // _ND_H
// vi: expandtab shiftwidth=4 softtabstop=4 tabstop=4
