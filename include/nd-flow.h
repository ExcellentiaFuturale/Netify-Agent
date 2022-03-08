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

#ifndef _ND_FLOW_H
#define _ND_FLOW_H

// XXX: These lengths are extracted from:
//      ndpi/src/include/ndpi_typedefs.h
//
// Unfortunately they don't define such constants so we have to define
// them here.  If they change in nDPI, they'll need to be updated
// manually.
#define ND_FLOW_UA_LEN      512     // User agent length
#define ND_FLOW_URL_LEN     512     // HTTP URL length
#define ND_FLOW_SSH_UALEN   48      // SSH user-agent (signature) length
#define ND_FLOW_TLS_CNLEN   256     // TLS SNI hostname/common-name length
                                    // Reference: RFC 4366
#define ND_FLOW_TLS_ORGLEN  64      // TLS certificate organization name length
#define ND_FLOW_TLS_JA3LEN  33      // TLS JA3 hash length (MD5)
#define ND_FLOW_DHCPFP_LEN  48      // DHCP fingerprint length
#define ND_FLOW_DHCPCI_LEN  96      // DHCP class identifier
#define ND_FLOW_MDNS_ANSLEN 96      // MDNS answer length

// BitTorrent info hash length
#define ND_FLOW_BTIHASH_LEN     SHA1_DIGEST_LENGTH

// SSL certificate fingerprint hash length
#define ND_FLOW_TLS_HASH_LEN    SHA1_DIGEST_LENGTH

// Kerberos fields
#define ND_FLOW_KERBEROS_FIELD  48
#define ND_FLOW_KERBEROS_HOST   ND_FLOW_KERBEROS_FIELD
#define ND_FLOW_KERBEROS_DOMAIN ND_FLOW_KERBEROS_FIELD
#define ND_FLOW_KERBEROS_USER   ND_FLOW_KERBEROS_FIELD

// Capture filename template
#define ND_FLOW_CAPTURE_TEMPLATE    ND_VOLATILE_STATEDIR "/nd-flow-XXXXXXXX.cap"
#define ND_FLOW_CAPTURE_SUB_OFFSET  (sizeof(ND_FLOW_CAPTURE_TEMPLATE) - 8 - 4 - 1)

typedef pair<const struct pcap_pkthdr *, const uint8_t *> nd_flow_push;
typedef vector<nd_flow_push> nd_flow_capture;

typedef unordered_map<string, string> nd_flow_kvmap;

class ndFlow
{
public:
    nd_ifaces::iterator iface;

    int16_t dpi_thread_id;

    uint8_t ip_version;
    uint8_t ip_protocol;

    uint16_t vlan_id;

    tcp_seq tcp_last_seq;

    uint64_t ts_first_seen;
    uint64_t ts_first_update;
    uint64_t ts_last_seen;

    enum {
        LOWER_UNKNOWN = 0x00,
        LOWER_LOCAL = 0x01,
        LOWER_OTHER = 0x02
    };

    uint8_t lower_map;

    enum {
        OTHER_UNKNOWN = 0x00,
        OTHER_UNSUPPORTED = 0x01,
        OTHER_LOCAL = 0x02,
        OTHER_MULTICAST = 0x03,
        OTHER_BROADCAST = 0x04,
        OTHER_REMOTE = 0x05,
        OTHER_ERROR = 0x06
    };

    uint8_t other_type;

    uint8_t lower_mac[ETH_ALEN];
    uint8_t upper_mac[ETH_ALEN];

    struct sockaddr_storage lower_addr;
    struct sockaddr_storage upper_addr;

    struct sockaddr_in *lower_addr4;
    struct sockaddr_in6 *lower_addr6;

    struct sockaddr_in *upper_addr4;
    struct sockaddr_in6 *upper_addr6;

    char lower_ip[INET6_ADDRSTRLEN];
    char upper_ip[INET6_ADDRSTRLEN];

    uint16_t lower_port;
    uint16_t upper_port;

    enum {
        TUNNEL_NONE = 0x00,
        TUNNEL_GTP = 0x01
    };

    uint8_t tunnel_type;

    uint64_t lower_bytes;
    uint64_t upper_bytes;
    uint64_t total_bytes;

    uint32_t lower_packets;
    uint32_t upper_packets;
    uint32_t total_packets;

    uint8_t detection_packets;

    nd_proto_id_t detected_protocol;
    nd_app_id_t detected_application;
   
    const char *detected_protocol_name;
    char *detected_application_name;

    struct ndpi_flow_struct *ndpi_flow;

    struct ndpi_id_struct *id_src;
    struct ndpi_id_struct *id_dst;

    uint8_t digest_lower[SHA1_DIGEST_LENGTH];
    uint8_t digest_mdata[SHA1_DIGEST_LENGTH];

    char host_server_name[ND_MAX_HOSTNAME];

    union {
        struct {
            char user_agent[ND_FLOW_UA_LEN];
            char url[ND_FLOW_URL_LEN];
        } http;

        struct {
            char fingerprint[ND_FLOW_DHCPFP_LEN];
            char class_ident[ND_FLOW_DHCPCI_LEN];
        } dhcp;

        struct {
            char client_agent[ND_FLOW_SSH_UALEN];
            char server_agent[ND_FLOW_SSH_UALEN];
        } ssh;

        struct {
            uint16_t version;
            uint16_t cipher_suite;
            char client_sni[ND_FLOW_TLS_CNLEN];
            char server_cn[ND_FLOW_TLS_CNLEN];
            char *server_names;
            unsigned server_names_length;
            char server_organization[ND_FLOW_TLS_ORGLEN];
            char client_ja3[ND_FLOW_TLS_JA3LEN];
            char server_ja3[ND_FLOW_TLS_JA3LEN];
            bool cert_fingerprint_found;
            char cert_fingerprint[ND_FLOW_TLS_HASH_LEN];
        } ssl;

        struct {
            bool tls;
        } smtp;

        struct {
            uint8_t info_hash_valid:1;
            char info_hash[ND_FLOW_BTIHASH_LEN];
        } bt;

        struct {
            char answer[ND_FLOW_MDNS_ANSLEN];
        } mdns;

        struct {
            char hostname[ND_FLOW_KERBEROS_HOST];
            char domain[ND_FLOW_KERBEROS_DOMAIN];
            char username[ND_FLOW_KERBEROS_USER];
        } kerberos;
    };

    struct {
        nd_flow_kvmap headers;
    } ssdp;

    enum {
        TYPE_LOWER,
        TYPE_UPPER,

        TYPE_MAX
    };

    enum {
        PRIVATE_LOWER = 0x01,
        PRIVATE_UPPER = 0x02
    };

    uint8_t privacy_mask;

    // Indicate flow origin.  This indicates which side sent the first packet.
    // XXX: If the service has missed a flow's initial packets, the origin's
    // accuracy would be 50%.
    enum {
        ORIGIN_UNKNOWN = 0x00,
        ORIGIN_LOWER = 0x01,
        ORIGIN_UPPER = 0x02
    };

    uint8_t origin;

    int direction;

    nd_flow_capture capture;
    char capture_filename[sizeof(ND_FLOW_CAPTURE_TEMPLATE)];

    // Start of conditional members.  These must be at the end or else access
    // from plugins compiled without various options will have incorrect
    // addresses
#if defined(_ND_USE_CONNTRACK) && defined(_ND_WITH_CONNTRACK_MDATA)
    uint32_t ct_id;
    uint32_t ct_mark;
#endif
#ifdef _ND_USE_NETLINK
    ndNetlinkAddressType lower_type;
    ndNetlinkAddressType upper_type;
#endif
    struct {
        atomic_bool ip_nat;
        atomic_bool tcp_fin;
        atomic_bool dhc_hit;
        atomic_bool detection_init;
        atomic_bool detection_complete;
        atomic_bool detection_expiring;
        atomic_bool detection_expired;
        atomic_bool detection_guessed;
        atomic_bool detection_updated;
    } flags;

    atomic_uint queued;

    union {
        struct {
            uint8_t version;
            uint8_t ip_version;
            uint32_t lower_teid;
            uint32_t upper_teid;
#ifdef _ND_USE_NETLINK
            ndNetlinkAddressType lower_type;
            ndNetlinkAddressType upper_type;
#endif
            struct sockaddr_storage lower_addr;
            struct sockaddr_storage upper_addr;
            char lower_ip[INET6_ADDRSTRLEN];
            char upper_ip[INET6_ADDRSTRLEN];
            uint16_t lower_port;
            uint16_t upper_port;
            uint8_t lower_map;
            uint8_t other_type;
        } gtp;
    };

    ndFlow(nd_ifaces::iterator iface);
    ndFlow(const ndFlow &flow);
    virtual ~ndFlow();

    void hash(const string &device, bool hash_mdata = false,
        const uint8_t *key = NULL, size_t key_length = 0);

    void push(const struct pcap_pkthdr *pkt_header, const uint8_t *pkt_data);

    int dump(pcap_t *pcap, const uint8_t *digest);

    void reset(void);

    void release(void);

    nd_proto_id_t master_protocol(void) const;

    bool has_dhcp_fingerprint(void) const;
    bool has_dhcp_class_ident(void) const;
    bool has_http_user_agent(void) const;
    bool has_http_url(void) const;
    bool has_ssh_client_agent(void) const;
    bool has_ssh_server_agent(void) const;
    bool has_ssl_client_sni(void) const;
    bool has_ssl_server_cn(void) const;
    bool has_ssl_server_names(void) const;
    bool has_ssl_server_organization(void) const;
    bool has_ssl_client_ja3(void) const;
    bool has_ssl_server_ja3(void) const;
    bool has_bt_info_hash(void) const;
    bool has_mdns_answer(void) const;
    bool has_ssdp_headers(void) const;
    bool has_kerberos_hostname(void) const;
    bool has_kerberos_domain(void) const;
    bool has_kerberos_username(void) const;

    void print(void) const;

    void update_lower_maps(void);
    void get_lower_map(
#ifdef _ND_USE_NETLINK
        ndNetlinkAddressType lt,
        ndNetlinkAddressType ut,
#endif
        uint8_t &lm, uint8_t &ot);

    enum nd_encode_include {
        ENCODE_NONE = 0x00,
        ENCODE_METADATA = 0x01,
        ENCODE_TUNNELS = 0x02,
        ENCODE_STATS = 0x04,
        ENCODE_ALL = (ENCODE_METADATA | ENCODE_TUNNELS | ENCODE_STATS)
    };

    void json_encode(json &j, uint8_t encode_includes = ENCODE_ALL);

    inline bool operator==(const ndFlow &f) const {
        if (lower_port != f.lower_port || upper_port != f.upper_port) return false;
        if (memcmp(&lower_addr, &f.lower_addr, sizeof(struct sockaddr_storage)) == 0 &&
            memcmp(&upper_addr, &f.upper_addr, sizeof(struct sockaddr_storage)) == 0)
            return true;
        return false;
    }

    inline ndFlow& operator+=(const ndFlow &f)
    {
        this->lower_bytes += f.lower_bytes;
        this->upper_bytes += f.upper_bytes;
        this->total_bytes += f.total_bytes;
        this->lower_packets += f.lower_packets;
        this->upper_packets += f.upper_packets;
        this->total_packets += f.total_packets;
        return *this;
    }
};

typedef unordered_map<string, ndFlow *> nd_flow_map;
typedef map<string, nd_flow_map *> nd_flows;
typedef pair<string, ndFlow *> nd_flow_pair;
typedef pair<nd_flow_map::iterator, bool> nd_flow_insert;

#endif // _ND_FLOW_H
// vi: expandtab shiftwidth=4 softtabstop=4 tabstop=4
