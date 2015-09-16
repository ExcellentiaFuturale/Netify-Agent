// ClearOS DPI Daemon
// Copyright (C) 2015 ClearFoundation <http://www.clearfoundation.com>
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

#ifndef _CDPI_H
#define _CDPI_H

#define CDPI_STATS_INTERVAL     15      // Collect stats every N seconds
#define CDPI_DETECTION_TICKS    1000    // Ticks-per-second (1000 = milliseconds)
#define CDPI_IDLE_SCAN_TIME     10      // Idle flow scan in milliseconds
#define CDPI_IDLE_FLOW_TIME     30000   // Purge idle flows older than this (30s)

#define CDPI_JSON_FILE_NAME     "/var/lib/cdpid/cdpid.json"
#define CDPI_JSON_FILE_USER     "root"
#define CDPI_JSON_FILE_GROUP    "webconfig"
#define CDPI_JSON_FILE_MODE     0640

#define CDPI_PCAP_SNAPLEN       1536    // Capture snap length
#define CDPI_PCAP_READ_TIMEOUT  500     // Milliseconds

struct cdpiDetectionStats
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
    uint64_t pkt_tcp;
    uint64_t pkt_udp;
    uint64_t pkt_ip_bytes;
    uint64_t pkt_wire_bytes;
    uint64_t pkt_discard_bytes;

    inline cdpiDetectionStats& operator+=(const cdpiDetectionStats &rhs) {
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
        pkt_tcp += rhs.pkt_tcp;
        pkt_udp += rhs.pkt_udp;
        pkt_ip_bytes += rhs.pkt_ip_bytes;
        pkt_wire_bytes += rhs.pkt_wire_bytes;
        pkt_discard_bytes += rhs.pkt_discard_bytes;
        return *this;
    }

    void print(const char *tag = "");
};

#define CDPI_SSL_CERTLEN        48      // SSL certificate length

struct cdpiFlow
{
    uint8_t version;

    uint8_t lower_mac[ETH_ALEN];
    uint8_t upper_mac[ETH_ALEN];

    struct in_addr lower_addr;
    struct in_addr upper_addr;

    struct in6_addr lower_addr6;
    struct in6_addr upper_addr6;

    char lower_ip[INET6_ADDRSTRLEN];
    char upper_ip[INET6_ADDRSTRLEN];

    uint16_t lower_port;
    uint16_t upper_port;

    uint8_t protocol;

    uint16_t vlan_id;

    uint64_t ts_last_seen;

    uint64_t bytes;
    uint32_t packets;

    bool detection_complete;
    bool detection_guessed;

    ndpi_protocol detected_protocol;

    struct ndpi_flow_struct *ndpi_flow;

    struct ndpi_id_struct *id_src;
    struct ndpi_id_struct *id_dst;

    char host_server_name[HOST_NAME_MAX];
    struct {
        char client_cert[CDPI_SSL_CERTLEN];
        char server_cert[CDPI_SSL_CERTLEN];
    } ssl;

    void hash(string &digest);

    inline bool operator==(const cdpiFlow &f) const {
        if (lower_port != f.lower_port || upper_port != f.upper_port) return false;
        switch (version) {
        case 4:
            if (memcmp(&lower_addr, &f.lower_addr, sizeof(struct in_addr)) == 0 &&
                memcmp(&upper_addr, &f.upper_addr, sizeof(struct in_addr)) == 0)
                return true;
            break;
        case 6:
            if (memcmp(&lower_addr6, &f.lower_addr6, sizeof(struct in6_addr)) == 0 &&
                memcmp(&upper_addr6, &f.upper_addr6, sizeof(struct in6_addr)) == 0)
                return true;
            break;
        }
        return false;
    }

    inline void release(void) {
        if (ndpi_flow != NULL) { ndpi_free_flow(ndpi_flow); ndpi_flow = NULL; }
        if (id_src != NULL) { delete id_src; id_src = NULL; }
        if (id_dst != NULL) { delete id_dst; id_dst = NULL; }
    }

    void print(const char *tag, struct ndpi_detection_module_struct *ndpi);
};

typedef unordered_map<string, struct cdpiFlow *> cdpi_flow_map;
typedef pair<string, struct cdpiFlow *> cdpi_flow_pair;
typedef pair<cdpi_flow_map::iterator, bool> cdpi_flow_insert;

#endif // _CDPI_H
// vi: expandtab shiftwidth=4 softtabstop=4 tabstop=4
