// Netify Agent
// Copyright (C) 2015-2019 eGloo Incorporated <http://www.egloo.ca>
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

#ifndef _ND_DETECTION_THREAD_H
#define _ND_DETECTION_THREAD_H

class ndSocketThread;

class ndDetectionThreadException : public runtime_error
{
public:
    explicit ndDetectionThreadException(const string &what_arg)
        : runtime_error(what_arg) { }
};

class ndDetectionThread : public ndThread
{
public:
    ndDetectionThread(
        const string &dev,
        bool internal,
#ifdef _ND_USE_NETLINK
        const string &netlink_dev,
        ndNetlink *netlink,
#endif
        ndSocketThread *thread_socket,
#ifdef _ND_USE_CONNTRACK
        ndConntrackThread *thread_conntrack,
#endif
        nd_flow_map *flow_map, nd_packet_stats *stats,
        nd_device_addrs *device_addrs = NULL,
        nd_dns_cache *dns_cache = NULL,
        long cpu = -1);
    virtual ~ndDetectionThread();

    struct ndpi_detection_module_struct *GetDetectionModule(void) {
        return ndpi;
    }
    virtual void *Entry(void);

    // XXX: The following public methods are Not thread-safe!

    nd_flow_map *GetFlows(void) { return flows; }

    int GetCaptureStats(struct pcap_stat &stats);

    void GetInterfaceRates(float &pps, float &bps);

protected:
    bool internal;
#ifdef _ND_USE_NETLINK
    string netlink_dev;
    ndNetlink *netlink;
#endif
    ndSocketThread *thread_socket;
#ifdef _ND_USE_CONNTRACK
    ndConntrackThread *thread_conntrack;
#endif
    pcap_t *pcap;
    int pcap_fd;
    string pcap_file;
    struct bpf_program pcap_filter;
    char pcap_errbuf[PCAP_ERRBUF_SIZE];
    int pcap_snaplen;
    int pcap_datalink_type;
    struct pcap_pkthdr *pkt_header;
    const uint8_t *pkt_data;
    uint64_t ts_pkt_last;
    uint64_t ts_last_idle_scan;
    struct ndpi_detection_module_struct *ndpi;
    uint32_t custom_proto_base;

    nd_flow_map *flows;
    nd_packet_stats *stats;
    nd_device_addrs *device_addrs;
    nd_dns_cache *dns_cache;
    ns_msg ns_h;

    // Last rate sample time
    uint64_t ts_rs;
    uint32_t rs_packets, rs_bytes;
    deque<uint32_t> rate_packets;
    deque<uint32_t> rate_bits;

    pcap_t *OpenCapture(void);

    void ProcessPacket(void);

    bool ProcessDNSResponse(
        const char *host, const uint8_t *pkt, uint16_t length);
};

typedef map<string, ndDetectionThread *> nd_threads;

#endif // _ND_DETECTION_THREAD_H
// vi: expandtab shiftwidth=4 softtabstop=4 tabstop=4
