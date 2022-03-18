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

#ifndef _ND_PROTOS_H
#define _ND_PROTOS_H

typedef enum {
    ND_PROTO_UNKNOWN                = 0,
    ND_PROTO_FTP_CONTROL            = 1,
    ND_PROTO_MAIL_POP               = 2,
    ND_PROTO_MAIL_SMTP              = 3,
    ND_PROTO_MAIL_IMAP              = 4,
    ND_PROTO_DNS                    = 5,
    ND_PROTO_IPP                    = 6,
    ND_PROTO_HTTP                   = 7,
    ND_PROTO_MDNS                   = 8,
    ND_PROTO_NTP                    = 9,
    ND_PROTO_NETBIOS                = 10,
    ND_PROTO_NFS                    = 11,
    ND_PROTO_SSDP                   = 12,
    ND_PROTO_BGP                    = 13,
    ND_PROTO_SNMP                   = 14,
    ND_PROTO_XDMCP                  = 15,
    ND_PROTO_SMBV1                  = 16,
    ND_PROTO_SYSLOG                 = 17,
    ND_PROTO_DHCP                   = 18,
    ND_PROTO_POSTGRES               = 19,
    ND_PROTO_MYSQL                  = 20,
    ND_PROTO_FTPS_CONTROL           = 21,
    ND_PROTO_DIRECT_DOWNLOAD_LINK   = 22,
    ND_PROTO_MAIL_POPS              = 23,
    ND_PROTO_APPLEJUICE             = 24,
    ND_PROTO_DIRECTCONNECT          = 25,
    ND_PROTO_DEPR26                 = 26,   // Deprecated: NTOP
    ND_PROTO_COAP                   = 27,
    ND_PROTO_VMWARE                 = 28,
    ND_PROTO_MAIL_SMTPS             = 29,
    ND_PROTO_DEPR30                 = 30,   // Deprecated: Facebook Zero
    ND_PROTO_UBNTAC2                = 31,
    ND_PROTO_KONTIKI                = 32,
    ND_PROTO_OPENFT                 = 33,
    ND_PROTO_FASTTRACK              = 34,
    ND_PROTO_GNUTELLA               = 35,
    ND_PROTO_EDONKEY                = 36,
    ND_PROTO_BITTORRENT             = 37,
    ND_PROTO_SKYPE_CALL             = 38,
    ND_PROTO_SIGNAL                 = 39,
    ND_PROTO_MEMCACHED              = 40,
    ND_PROTO_SMBV23                 = 41,
    ND_PROTO_MINING                 = 42,
    ND_PROTO_NEST_LOG_SINK          = 43,
    ND_PROTO_MODBUS                 = 44,
    ND_PROTO_DEPR45                 = 45,   // Deprecated: WhatsApp Video
    ND_PROTO_DATASAVER              = 46,
    ND_PROTO_XBOX                   = 47,
    ND_PROTO_QQ                     = 48,
    ND_PROTO_TIKTOK                 = 49,
    ND_PROTO_RTSP                   = 50,
    ND_PROTO_MAIL_IMAPS             = 51,
    ND_PROTO_ICECAST                = 52,
    ND_PROTO_DEPR53                 = 53,   // Deprecated: PPLive
    ND_PROTO_PPSTREAM               = 54,
    ND_PROTO_ZATTOO                 = 55,
    ND_PROTO_SHOUTCAST              = 56,
    ND_PROTO_SOPCAST                = 57,
    ND_PROTO_DEPR58                 = 58,   // Deprecated: TVANTS
    ND_PROTO_TVUPLAYER              = 59,
    ND_PROTO_DEPR60                 = 60,   // Deprecated: HTTP_Download
    ND_PROTO_QQLIVE                 = 61,
    ND_PROTO_THUNDER                = 62,
    ND_PROTO_DEPR63                 = 63,   // Deprecated: SoulSeek
    ND_PROTO_DEPR64                 = 64,   // Deprecated: SSL No Cert
    ND_PROTO_IRC                    = 65,
    ND_PROTO_AYIYA                  = 66,
    ND_PROTO_XMPP                   = 67,   // Renamed: Jabber
    ND_PROTO_FREE68                 = 68,
    ND_PROTO_FREE69                 = 69,
    ND_PROTO_YAHOO                  = 70,   // TODO: Delete.
    ND_PROTO_FREE71                 = 71,
    ND_PROTO_FREE72                 = 72,
    ND_PROTO_IP_VRRP                = 73,
    ND_PROTO_STEAM                  = 74,
    ND_PROTO_HALFLIFE2              = 75,
    ND_PROTO_WORLDOFWARCRAFT        = 76,
    ND_PROTO_TELNET                 = 77,
    ND_PROTO_STUN                   = 78,
    ND_PROTO_IP_IPSEC               = 79,
    ND_PROTO_IP_GRE                 = 80,
    ND_PROTO_IP_ICMP                = 81,
    ND_PROTO_IP_IGMP                = 82,
    ND_PROTO_IP_EGP                 = 83,
    ND_PROTO_IP_SCTP                = 84,
    ND_PROTO_IP_OSPF                = 85,
    ND_PROTO_IP_IP_IN_IP            = 86,
    ND_PROTO_RTP                    = 87,
    ND_PROTO_RDP                    = 88,
    ND_PROTO_VNC                    = 89,
    ND_PROTO_DEPR90                 = 90,   // Deprecated: pcAnywhere
    ND_PROTO_TLS                    = 91,
    ND_PROTO_SSH                    = 92,
    ND_PROTO_NNTP                   = 93,
    ND_PROTO_MGCP                   = 94,
    ND_PROTO_IAX                    = 95,
    ND_PROTO_TFTP                   = 96,
    ND_PROTO_AFP                    = 97,
    ND_PROTO_STEALTHNET             = 98,
    ND_PROTO_AIMINI                 = 99,
    ND_PROTO_SIP                    = 100,
    ND_PROTO_TRUPHONE               = 101,
    ND_PROTO_IP_ICMPV6              = 102,
    ND_PROTO_DHCPV6                 = 103,
    ND_PROTO_ARMAGETRON             = 104,
    ND_PROTO_CROSSFIRE              = 105,
    ND_PROTO_DOFUS                  = 106,
    ND_PROTO_FIESTA                 = 107,
    ND_PROTO_FLORENSIA              = 108,
    ND_PROTO_GUILDWARS              = 109,
    ND_PROTO_FREE110                = 110,
    ND_PROTO_KERBEROS               = 111,
    ND_PROTO_LDAP                   = 112,
    ND_PROTO_MAPLESTORY             = 113,
    ND_PROTO_MSSQL_TDS              = 114,
    ND_PROTO_PPTP                   = 115,
    ND_PROTO_WARCRAFT3              = 116,
    ND_PROTO_WORLDOFKUNGFU          = 117,
    ND_PROTO_DEPR118                = 118,  // Deprecated: Slack
    ND_PROTO_FREE119                = 119,
    ND_PROTO_FREE120                = 120,
    ND_PROTO_DROPBOX                = 121,
    ND_PROTO_FREE122                = 122,
    ND_PROTO_FREE123                = 123,
    ND_PROTO_FREE124                = 124,
    ND_PROTO_DEPR125                = 125,  // Deprecated: Skype
    ND_PROTO_FREE126                = 126,
    ND_PROTO_RPC                    = 127,  // Renamed: DCERPC -> RPC
    ND_PROTO_NETFLOW                = 128,
    ND_PROTO_SFLOW                  = 129,
    ND_PROTO_HTTP_CONNECT           = 130,
    ND_PROTO_HTTP_PROXY             = 131,
    ND_PROTO_CITRIX                 = 132,
    ND_PROTO_FREE133                = 133,
    ND_PROTO_FREE134                = 134,
    ND_PROTO_DEPR135                = 135,  // Deprecated: Waze
    ND_PROTO_FREE136                = 136,
    ND_PROTO_DEPR137                = 137,  // Deprecated: Generic (old category matching)
    ND_PROTO_CHECKMK                = 138,
    ND_PROTO_AJP                    = 139,
    ND_PROTO_DEPR140                = 140,  // Deprecated: Apple
    ND_PROTO_FREE141                = 141,
    ND_PROTO_WHATSAPP               = 142,
    ND_PROTO_DEPR143                = 143,  // Deprecated: Apple iCloud
    ND_PROTO_VIBER                  = 144,
    ND_PROTO_DEPR145                = 145,  // Deprecated: Apple iTunes
    ND_PROTO_RADIUS                 = 146,
    ND_PROTO_FREE147                = 147,
    ND_PROTO_TEAMVIEWER             = 148,
    ND_PROTO_FREE149                = 149,
    ND_PROTO_LOTUS_NOTES            = 150,
    ND_PROTO_SAP                    = 151,
    ND_PROTO_GTP                    = 152,
    ND_PROTO_WSD                    = 153,  // Renamed: UPnP
    ND_PROTO_LLMNR                  = 154,
    ND_PROTO_REMOTE_SCAN            = 155,
    ND_PROTO_SPOTIFY                = 156,
    ND_PROTO_DEPR157                = 157,  // Deprecated: FB? Messenger
    ND_PROTO_H323                   = 158,
    ND_PROTO_OPENVPN                = 159,
    ND_PROTO_NOE                    = 160,  // Alcatel new office environment
    ND_PROTO_CISCO_VPN              = 161,
    ND_PROTO_TEAMSPEAK              = 162,
    ND_PROTO_TOR                    = 163,  // TODO: Delete (from nDPI).
    ND_PROTO_CISCO_SKINNY           = 164,
    ND_PROTO_RTCP                   = 165,
    ND_PROTO_RSYNC                  = 166,
    ND_PROTO_ORACLE                 = 167,
    ND_PROTO_CORBA                  = 168,
    ND_PROTO_FREE169                = 169,
    ND_PROTO_WHOIS_DAS              = 170,
    ND_PROTO_COLLECTD               = 171,
    ND_PROTO_SOCKS                  = 172,
    ND_PROTO_NINTENDO               = 173,
    ND_PROTO_RTMP                   = 174,
    ND_PROTO_FTP_DATA               = 175,
    ND_PROTO_FREE176                = 176,
    ND_PROTO_ZMQ                    = 177,
    ND_PROTO_FREE178                = 178,
    ND_PROTO_FREE179                = 179,
    ND_PROTO_FREE180                = 180,
    ND_PROTO_MEGACO                 = 181,
    ND_PROTO_REDIS                  = 182,
    ND_PROTO_FREE183                = 183,
    ND_PROTO_VHUA                   = 184,
    ND_PROTO_TELEGRAM               = 185,
    ND_PROTO_FREE186                = 186,
    ND_PROTO_FREE187                = 187,
    ND_PROTO_QUIC                   = 188,
    ND_PROTO_WHATSAPP_VOICE         = 189,
    ND_PROTO_EAQ                    = 190,
    ND_PROTO_OOKLA                  = 191,
    ND_PROTO_AMQP                   = 192,
    ND_PROTO_DEPR193                = 193,  // Deprecated: Kakaotalk
    ND_PROTO_KAKAOTALK_VOICE        = 194,
    ND_PROTO_FREE195                = 195,
    ND_PROTO_HTTPS                  = 196,
    ND_PROTO_FREE197                = 197,
    ND_PROTO_MPEGTS                 = 198,
    ND_PROTO_FREE199                = 199,
    ND_PROTO_FREE200                = 200,
    ND_PROTO_FREE201                = 201,
    ND_PROTO_FREE202                = 202,
    ND_PROTO_FREE203                = 203,
    ND_PROTO_BJNP                   = 204,
    ND_PROTO_FREE205                = 205,
    ND_PROTO_WIREGUARD              = 206,
    ND_PROTO_SMPP                   = 207,
    ND_PROTO_FREE208                = 208,
    ND_PROTO_TINC                   = 209,
    ND_PROTO_FREE210                = 210,
    ND_PROTO_FREE211                = 211,
    ND_PROTO_FREE212                = 212,
    ND_PROTO_STARCRAFT              = 213,
    ND_PROTO_TEREDO                 = 214,
    ND_PROTO_DEPR215                = 215,  // Deprecated: Hotspot Shield VPN
    ND_PROTO_DEPR216                = 216,  // Deprecated: HEP
    ND_PROTO_FREE217                = 217,
    ND_PROTO_FREE218                = 218,
    ND_PROTO_FREE219                = 219,
    ND_PROTO_FREE220                = 220,
    ND_PROTO_FREE221                = 221,
    ND_PROTO_MQTT                   = 222,
    ND_PROTO_RX                     = 223,
    ND_PROTO_FREE224                = 224,
    ND_PROTO_FREE225                = 225,
    ND_PROTO_GIT                    = 226,
    ND_PROTO_DRDA                   = 227,
    ND_PROTO_FREE228                = 228,
    ND_PROTO_SOMEIP                 = 229,
    ND_PROTO_FIX                    = 230,
    ND_PROTO_FREE231                = 231,
    ND_PROTO_FREE232                = 232,
    ND_PROTO_FREE233                = 233,
    ND_PROTO_FREE234                = 234,
    ND_PROTO_CSGO                   = 235,
    ND_PROTO_LISP                   = 236,
    ND_PROTO_DIAMETER               = 237,
    ND_PROTO_APPLE_PUSH             = 238,
    ND_PROTO_FREE239                = 239,
    ND_PROTO_FREE240                = 240,
    ND_PROTO_FREE241                = 241,
    ND_PROTO_FREE242                = 242,
    ND_PROTO_DOH                    = 243,
    ND_PROTO_DTLS                   = 244,
    ND_PROTO_GOOGLE_MEET_DUO        = 245,
    ND_PROTO_WHATSAPP_CALL          = 246,
    ND_PROTO_SKYPE_TEAMS            = 247,
    ND_PROTO_ZOOM                   = 248,
    ND_PROTO_FREE249                = 249,
    ND_PROTO_FREE250                = 250,
    ND_PROTO_FREE251                = 251,
    ND_PROTO_FREE252                = 252,
    ND_PROTO_FREE253                = 253,
    ND_PROTO_FREE254                = 254,
    ND_PROTO_SNAPCHAT_CALL          = 255,
    ND_PROTO_FTPS_DATA              = 256,
    ND_PROTO_SIPS                   = 257,
    ND_PROTO_MQTTS                  = 258,
    ND_PROTO_NNTPS                  = 259,
    ND_PROTO_DOT                    = 260,
    ND_PROTO_DOQ                    = 261,  // TODO: Refine QUIC via ALPN (doq)
    ND_PROTO_AMAZON_VIDEO           = 262,
    ND_PROTO_AMONG_US               = 263,
    ND_PROTO_AVAST_SDNS             = 264,
    ND_PROTO_CAPWAP                 = 265,
    ND_PROTO_CASSANDRA              = 266,
    ND_PROTO_CPHA                   = 267,
    ND_PROTO_DNP3                   = 268,
    ND_PROTO_DNSCRYPT               = 269,

    // EtherNet/IP (explicit messaging)
    // https://www.odva.org/wp-content/uploads/2021/05/PUB00138R7_Tech-Series-EtherNetIP.pdf
    ND_PROTO_ETHERNET_IP            = 270,

    ND_PROTO_GENSHIN_IMPACT         = 271,
    ND_PROTO_GTP_C                  = 272,
    ND_PROTO_GTP_P                  = 273,
    ND_PROTO_GTP_U                  = 274,
    ND_PROTO_HP_VIRTGRP             = 275,
    ND_PROTO_CISCO_HSRP             = 276,
    ND_PROTO_IEC60870_5_104         = 277, // Extension for industrial 104 protocol recognition
    ND_PROTO_IMO                    = 278, // No idea what this is.
    ND_PROTO_IRCS                   = 279, // IRC over TLS
    ND_PROTO_MONGODB                = 280, // MongoDB

    // NATS: Connective Technology for Adaptive Edge & Distributed Systems
    // https://docs.nats.io/
    ND_PROTO_NATS                   = 281,

    // S7comm (S7 Communication) is a Siemens proprietary protocol that runs
    // between programmable logic controllers (PLCs) of the Siemens S7-300/400 family.
    ND_PROTO_S7COMM                 = 282,

    ND_PROTO_SOAP                   = 283,
    ND_PROTO_TARGUS_GETDATA         = 284, // Targus Dataspeed (speedtest).
    ND_PROTO_VXLAN                  = 285, // Virtual Extensible LAN.

    ND_PROTO_MAX,
    ND_PROTO_TODO                   = 0xffffffff
} nd_proto_id_t;

typedef unordered_map<unsigned, const char *> nd_protos_t;

const nd_protos_t nd_protos = {
    { ND_PROTO_AFP, "AFP" },
    { ND_PROTO_AIMINI, "Aimini" },
    { ND_PROTO_AJP, "AJP" },
    { ND_PROTO_AMAZON_VIDEO, "AmazonVideo" },
    { ND_PROTO_AMONG_US, "AmongUs" },
    { ND_PROTO_AMQP, "AMQP" },
    { ND_PROTO_APPLEJUICE, "APPLJ" },
    { ND_PROTO_APPLE_PUSH, "Apple/Push" },
    { ND_PROTO_ARMAGETRON, "Armagetron" },
    { ND_PROTO_AVAST_SDNS, "AVASTSecureDNS" },
    { ND_PROTO_AYIYA, "Ayiya" },
    { ND_PROTO_BGP, "BGP" },
    { ND_PROTO_BITTORRENT, "BitTorrent" },
    { ND_PROTO_BJNP, "BJNP" },
    { ND_PROTO_CAPWAP, "CAPWAP" },
    { ND_PROTO_CASSANDRA, "Cassandra" },
    { ND_PROTO_CHECKMK, "CHECKMK" },
    { ND_PROTO_CISCO_HSRP, "Cisco/HSRP" },
    { ND_PROTO_CISCO_SKINNY, "Cisco/Skinny" },
    { ND_PROTO_CISCO_VPN, "Cisco/VPN" },
    { ND_PROTO_CITRIX, "Citrix" },
    { ND_PROTO_COAP, "COAP" },
    { ND_PROTO_COLLECTD, "Collectd" },
    { ND_PROTO_CORBA, "Corba" },
    { ND_PROTO_CPHA, "CheckPointHA" },
    { ND_PROTO_CROSSFIRE, "Crossfire" },
    { ND_PROTO_CSGO, "CSGO" },
    { ND_PROTO_DHCP, "DHCP" },
    { ND_PROTO_DHCPV6, "DHCPv6" },
    { ND_PROTO_DIAMETER, "Diameter" },
    { ND_PROTO_DIRECTCONNECT, "DConnect" },
    { ND_PROTO_DIRECT_DOWNLOAD_LINK, "DDLink" },
    { ND_PROTO_DNP3, "DNP3" },
    { ND_PROTO_DNSCRYPT, "DNSCrypt" },
    { ND_PROTO_DNS, "DNS" },
    { ND_PROTO_DOFUS, "Dofus" },
    { ND_PROTO_DOH, "DoH" },
    { ND_PROTO_DOQ, "DoQ" },
    { ND_PROTO_DOT, "DoT" },
    { ND_PROTO_DRDA, "DRDA" },
    { ND_PROTO_DROPBOX, "Dropbox" },
    { ND_PROTO_DTLS, "DTLS" },
    { ND_PROTO_EAQ, "EAQ" },
    { ND_PROTO_EDONKEY, "eDonkey" },
    { ND_PROTO_ETHERNET_IP, "EtherNet/IP" },
    { ND_PROTO_FASTTRACK, "FastTrack" },
    { ND_PROTO_FIESTA, "Fiesta" },
    { ND_PROTO_FIX, "FIX" },
    { ND_PROTO_FLORENSIA, "Florensia" },
    { ND_PROTO_FTP_CONTROL, "FTP/C" },
    { ND_PROTO_FTP_DATA, "FTP/D" },
    { ND_PROTO_FTPS_CONTROL, "FTP/S/C" },
    { ND_PROTO_FTPS_DATA, "FTP/S/D" },
    { ND_PROTO_GENSHIN_IMPACT, "Genshin Impact" },
    { ND_PROTO_GIT, "Git" },
    { ND_PROTO_GNUTELLA, "Gnutella" },
    { ND_PROTO_GOOGLE_MEET_DUO, "Google/Meet/Duo" },
    { ND_PROTO_GTP_C, "GTP/C" },
    { ND_PROTO_GTP, "GTP" },
    { ND_PROTO_GTP_P, "GTP/P" },
    { ND_PROTO_GTP_U, "GTP/U" },
    { ND_PROTO_GUILDWARS, "Guildwars" },
    { ND_PROTO_H323, "H323" },
    { ND_PROTO_HALFLIFE2, "HalfLife2" },
    { ND_PROTO_HP_VIRTGRP, "HP/VirtGrp" },
    { ND_PROTO_HTTP_CONNECT, "HTTP/Connect" },
    { ND_PROTO_HTTP, "HTTP" },
    { ND_PROTO_HTTP_PROXY, "HTTP/Proxy" },
    { ND_PROTO_HTTPS, "HTTP/S" },
    { ND_PROTO_IAX, "IAX" },
    { ND_PROTO_ICECAST, "IceCast" },
    { ND_PROTO_IEC60870_5_104, "IEC60870/5/104" },
    { ND_PROTO_IMO, "IMO" },
    { ND_PROTO_IP_EGP, "EGP" },
    { ND_PROTO_IP_GRE, "GRE" },
    { ND_PROTO_IP_ICMP, "ICMP" },
    { ND_PROTO_IP_ICMPV6, "ICMPv6" },
    { ND_PROTO_IP_IGMP, "IGMP" },
    { ND_PROTO_IP_IP_IN_IP, "IPinIP" },
    { ND_PROTO_IP_IPSEC, "IPSEC" },
    { ND_PROTO_IP_OSPF, "OSPF" },
    { ND_PROTO_IPP, "IPP" },
    { ND_PROTO_IP_SCTP, "SCTP" },
    { ND_PROTO_IP_VRRP, "VRRP" },
    { ND_PROTO_IRC, "IRC" },
    { ND_PROTO_IRCS, "IRC/S" },
    { ND_PROTO_KAKAOTALK_VOICE, "KakaoTalk/Voice" },
    { ND_PROTO_KERBEROS, "Kerberos" },
    { ND_PROTO_KONTIKI, "Kontiki" },
    { ND_PROTO_LDAP, "LDAP" },
    { ND_PROTO_LISP, "LISP" },
    { ND_PROTO_LLMNR, "LLMNR" },
    { ND_PROTO_LOTUS_NOTES, "LotusNotes" },
    { ND_PROTO_MAIL_IMAP, "IMAP" },
    { ND_PROTO_MAIL_IMAPS, "IMAP/S" },
    { ND_PROTO_MAIL_POP, "POP3" },
    { ND_PROTO_MAIL_POPS, "POP3/S" },
    { ND_PROTO_MAIL_SMTP, "SMTP" },
    { ND_PROTO_MAIL_SMTPS, "SMTP/S" },
    { ND_PROTO_MAPLESTORY, "MapleStory" },
    { ND_PROTO_MDNS, "MDNS" },
    { ND_PROTO_MEGACO, "Megaco" },
    { ND_PROTO_MEMCACHED, "Memcached" },
    { ND_PROTO_MGCP, "MGCP" },
    { ND_PROTO_MINING, "Mining" },
    { ND_PROTO_MODBUS, "Modbus" },
    { ND_PROTO_MONGODB, "MongoDB" },
    { ND_PROTO_MPEGTS, "MPEGTS" },
    { ND_PROTO_MQTT, "MQTT" },
    { ND_PROTO_MQTTS, "MQTT/S" },
    { ND_PROTO_MSSQL_TDS, "MSSQL/TDS" },
    { ND_PROTO_MYSQL, "MYSQL" },
    { ND_PROTO_NATS, "NATS" },
    { ND_PROTO_NEST_LOG_SINK, "NestLog" },
    { ND_PROTO_NETBIOS, "NETBIOS" },
    { ND_PROTO_NETFLOW, "NetFlow" },
    { ND_PROTO_NFS, "NFS" },
    { ND_PROTO_NINTENDO, "Nintendo" },
    { ND_PROTO_NNTP, "NNTP" },
    { ND_PROTO_NNTPS, "NNTP/S" },
    { ND_PROTO_NOE, "NOE" },
    { ND_PROTO_NTP, "NTP" },
    { ND_PROTO_OOKLA, "OOKLA" },
    { ND_PROTO_OPENFT, "OpenFT" },
    { ND_PROTO_OPENVPN, "OpenVPN" },
    { ND_PROTO_ORACLE, "Oracle" },
    { ND_PROTO_POSTGRES, "PGSQL" },
    { ND_PROTO_PPSTREAM, "PPStream" },
    { ND_PROTO_PPTP, "PPTP" },
    { ND_PROTO_QQLIVE, "QQLive" },
    { ND_PROTO_QQ, "QQ" },
    { ND_PROTO_QUIC, "QUIC" },
    { ND_PROTO_RADIUS, "RADIUS" },
    { ND_PROTO_RDP, "RDP" },
    { ND_PROTO_REDIS, "Redis" },
    { ND_PROTO_REMOTE_SCAN, "RemoteScan" },
    { ND_PROTO_RPC, "RPC" },
    { ND_PROTO_RSYNC, "RSYNC" },
    { ND_PROTO_RTCP, "RTCP" },
    { ND_PROTO_RTMP, "RTMP" },
    { ND_PROTO_RTP, "RTP" },
    { ND_PROTO_RTSP, "RTSP" },
    { ND_PROTO_RX, "RX" },
    { ND_PROTO_S7COMM, "S7comm" },
    { ND_PROTO_SAP, "SAP" },
    { ND_PROTO_SFLOW, "SFlow" },
    { ND_PROTO_SHOUTCAST, "ShoutCast" },
    { ND_PROTO_SIGNAL, "Signal" },
    { ND_PROTO_SIP, "SIP" },
    { ND_PROTO_SIPS, "SIP/S" },
    { ND_PROTO_SKYPE_CALL, "SkypeCall" },
    { ND_PROTO_SKYPE_TEAMS, "Skype/Teams" },
    { ND_PROTO_SMBV1, "SMBv1" },
    { ND_PROTO_SMBV23, "SMBv23" },
    { ND_PROTO_SMPP, "SMPP" },
    { ND_PROTO_SNAPCHAT_CALL, "Snapchat/Call" },
    { ND_PROTO_SNMP, "SNMP" },
    { ND_PROTO_SOAP, "SOAP" },
    { ND_PROTO_SOCKS, "SOCKS" },
    { ND_PROTO_SOMEIP, "SOMEIP" },
    { ND_PROTO_SOPCAST, "Sopcast" },
    { ND_PROTO_SPOTIFY, "Spotify" },
    { ND_PROTO_SSDP, "SSDP" },
    { ND_PROTO_SSH, "SSH" },
    { ND_PROTO_STARCRAFT, "Starcraft" },
    { ND_PROTO_STEALTHNET, "Stealthnet" },
    { ND_PROTO_STEAM, "Steam" },
    { ND_PROTO_STUN, "STUN" },
    { ND_PROTO_SYSLOG, "SYSLOG" },
    { ND_PROTO_TARGUS_GETDATA, "Targus/Dataspeed" },
    { ND_PROTO_TEAMSPEAK, "TeamSpeak" },
    { ND_PROTO_TEAMVIEWER, "TeamViewer" },
    { ND_PROTO_TELEGRAM, "Telegram" },
    { ND_PROTO_TELNET, "Telnet" },
    { ND_PROTO_TEREDO, "Teredo" },
    { ND_PROTO_TFTP, "TFTP" },
    { ND_PROTO_THUNDER, "Thunder" },
    { ND_PROTO_TINC, "TINC" },
    { ND_PROTO_TLS, "TLS" },
    { ND_PROTO_TODO, "TODO" },
    { ND_PROTO_TOR, "TOR" },
    { ND_PROTO_TRUPHONE, "TruPhone" },
    { ND_PROTO_TVUPLAYER, "TVUplayer" },
    { ND_PROTO_UBNTAC2, "UBNTAC2" },
    { ND_PROTO_UNKNOWN, "Unknown" },
    { ND_PROTO_VHUA, "VHUA" },
    { ND_PROTO_VIBER, "Viber" },
    { ND_PROTO_VMWARE, "VMWARE" },
    { ND_PROTO_VNC, "VNC" },
    { ND_PROTO_VXLAN, "VXLAN" },
    { ND_PROTO_WARCRAFT3, "Warcraft3" },
    { ND_PROTO_WHATSAPP_CALL, "WhatsApp/Call" },
    { ND_PROTO_WHATSAPP_VOICE, "WhatsApp/Voice" },
    { ND_PROTO_WHATSAPP, "WhatsApp" },
    { ND_PROTO_WHOIS_DAS, "Whois/DAS" },
    { ND_PROTO_WIREGUARD, "WireGuard" },
    { ND_PROTO_WORLDOFKUNGFU, "WoKungFu" },
    { ND_PROTO_WORLDOFWARCRAFT, "WoW" },
    { ND_PROTO_WSD, "WSD" },
    { ND_PROTO_XBOX, "Xbox" },
    { ND_PROTO_XDMCP, "XDMCP" },
    { ND_PROTO_XMPP, "XMPP" },
    { ND_PROTO_YAHOO, "Yahoo" },
    { ND_PROTO_ZATTOO, "Zattoo" },
    { ND_PROTO_ZMQ, "ZMQ" },
    { ND_PROTO_ZOOM, "ZOOM" },
};

inline const char *nd_proto_get_name(nd_proto_id_t id)
{
    nd_protos_t::const_iterator it;
    if ((it = nd_protos.find(id)) == nd_protos.end())
        return "Unknown";
    return it->second;
}

typedef unordered_map<uint16_t, nd_proto_id_t> nd_ndpi_proto_t;

const nd_ndpi_proto_t nd_ndpi_protos = {
    { NDPI_PROTOCOL_AFP, ND_PROTO_AFP },
    { NDPI_PROTOCOL_AIMINI, ND_PROTO_AIMINI },
    { NDPI_PROTOCOL_AJP, ND_PROTO_AJP },
    { NDPI_PROTOCOL_AMAZON_VIDEO, ND_PROTO_AMAZON_VIDEO },
    { NDPI_PROTOCOL_AMONG_US, ND_PROTO_AMONG_US },
    { NDPI_PROTOCOL_AMQP, ND_PROTO_AMQP },
    { NDPI_PROTOCOL_APPLEJUICE, ND_PROTO_APPLEJUICE },
    { NDPI_PROTOCOL_APPLE_PUSH, ND_PROTO_APPLE_PUSH },
    { NDPI_PROTOCOL_ARMAGETRON, ND_PROTO_ARMAGETRON },
    { NDPI_PROTOCOL_AVAST_SECUREDNS, ND_PROTO_AVAST_SDNS },
    { NDPI_PROTOCOL_AYIYA, ND_PROTO_AYIYA },
    { NDPI_PROTOCOL_BGP, ND_PROTO_BGP },
    { NDPI_PROTOCOL_BITTORRENT, ND_PROTO_BITTORRENT },
    { NDPI_PROTOCOL_BJNP, ND_PROTO_BJNP },
    { NDPI_PROTOCOL_CAPWAP, ND_PROTO_CAPWAP },
    { NDPI_PROTOCOL_CASSANDRA, ND_PROTO_CASSANDRA },
    { NDPI_PROTOCOL_CHECKMK, ND_PROTO_CHECKMK },
    { NDPI_PROTOCOL_CISCOVPN, ND_PROTO_CISCO_VPN },
    { NDPI_PROTOCOL_CITRIX, ND_PROTO_CITRIX },
    { NDPI_PROTOCOL_COAP, ND_PROTO_COAP },
    { NDPI_PROTOCOL_COLLECTD, ND_PROTO_COLLECTD },
    { NDPI_PROTOCOL_CORBA, ND_PROTO_CORBA },
    { NDPI_PROTOCOL_CPHA, ND_PROTO_CPHA },
    { NDPI_PROTOCOL_CROSSFIRE, ND_PROTO_CROSSFIRE },
    { NDPI_PROTOCOL_CSGO, ND_PROTO_CSGO },
    { NDPI_PROTOCOL_DATASAVER, ND_PROTO_DATASAVER },
    { NDPI_PROTOCOL_DHCP, ND_PROTO_DHCP },
    { NDPI_PROTOCOL_DHCPV6, ND_PROTO_DHCPV6 },
    { NDPI_PROTOCOL_DIAMETER, ND_PROTO_DIAMETER },
    { NDPI_PROTOCOL_DIRECTCONNECT, ND_PROTO_DIRECTCONNECT },
    { NDPI_PROTOCOL_DIRECT_DOWNLOAD_LINK, ND_PROTO_DIRECT_DOWNLOAD_LINK },
    { NDPI_PROTOCOL_DNP3, ND_PROTO_DNP3 },
    { NDPI_PROTOCOL_DNSCRYPT, ND_PROTO_DNSCRYPT },
    { NDPI_PROTOCOL_DNS, ND_PROTO_DNS },
    { NDPI_PROTOCOL_DOFUS, ND_PROTO_DOFUS },
    { NDPI_PROTOCOL_DOH_DOT, ND_PROTO_DOH },
    { NDPI_PROTOCOL_DRDA, ND_PROTO_DRDA },
    { NDPI_PROTOCOL_DROPBOX, ND_PROTO_DROPBOX },
    { NDPI_PROTOCOL_DTLS, ND_PROTO_DTLS },
    { NDPI_PROTOCOL_EAQ, ND_PROTO_EAQ },
    { NDPI_PROTOCOL_EDONKEY, ND_PROTO_EDONKEY },
    { NDPI_PROTOCOL_ETHERNET_IP, ND_PROTO_ETHERNET_IP },
    { NDPI_PROTOCOL_FASTTRACK, ND_PROTO_FASTTRACK },
    { NDPI_PROTOCOL_FIESTA, ND_PROTO_FIESTA },
    { NDPI_PROTOCOL_FIX, ND_PROTO_FIX },
    { NDPI_PROTOCOL_FLORENSIA, ND_PROTO_FLORENSIA },
    { NDPI_PROTOCOL_FTP_CONTROL, ND_PROTO_FTP_CONTROL },
    { NDPI_PROTOCOL_FTP_DATA, ND_PROTO_FTP_DATA },
    { NDPI_PROTOCOL_GENSHIN_IMPACT, ND_PROTO_GENSHIN_IMPACT },
    { NDPI_PROTOCOL_GIT, ND_PROTO_GIT },
    { NDPI_PROTOCOL_GNUTELLA, ND_PROTO_GNUTELLA },
    { NDPI_PROTOCOL_GTP_C, ND_PROTO_GTP_C },
    { NDPI_PROTOCOL_GTP, ND_PROTO_GTP },
    { NDPI_PROTOCOL_GTP_PRIME, ND_PROTO_GTP_P },
    { NDPI_PROTOCOL_GTP_U, ND_PROTO_GTP_U },
    { NDPI_PROTOCOL_GUILDWARS, ND_PROTO_GUILDWARS },
    { NDPI_PROTOCOL_H323, ND_PROTO_H323 },
    { NDPI_PROTOCOL_HALFLIFE2, ND_PROTO_HALFLIFE2 },
    { NDPI_PROTOCOL_HANGOUT_DUO, ND_PROTO_GOOGLE_MEET_DUO },
    { NDPI_PROTOCOL_HPVIRTGRP, ND_PROTO_HP_VIRTGRP },
    { NDPI_PROTOCOL_HSRP, ND_PROTO_CISCO_HSRP },
    { NDPI_PROTOCOL_HTTP_CONNECT, ND_PROTO_HTTP_CONNECT },
    { NDPI_PROTOCOL_HTTP, ND_PROTO_HTTP },
    { NDPI_PROTOCOL_HTTP_PROXY, ND_PROTO_HTTP_PROXY },
    { NDPI_PROTOCOL_IAX, ND_PROTO_IAX },
    { NDPI_PROTOCOL_ICECAST, ND_PROTO_ICECAST },
    { NDPI_PROTOCOL_IEC60870, ND_PROTO_IEC60870_5_104 },
    { NDPI_PROTOCOL_IMO, ND_PROTO_IMO },
    { NDPI_PROTOCOL_IP_EGP, ND_PROTO_IP_EGP },
    { NDPI_PROTOCOL_IP_GRE, ND_PROTO_IP_GRE },
    { NDPI_PROTOCOL_IP_ICMP, ND_PROTO_IP_ICMP },
    { NDPI_PROTOCOL_IP_ICMPV6, ND_PROTO_IP_ICMPV6 },
    { NDPI_PROTOCOL_IP_IGMP, ND_PROTO_IP_IGMP },
    { NDPI_PROTOCOL_IP_IP_IN_IP, ND_PROTO_IP_IP_IN_IP },
    { NDPI_PROTOCOL_IP_IPSEC, ND_PROTO_IP_IPSEC },
    { NDPI_PROTOCOL_IP_OSPF, ND_PROTO_IP_OSPF },
    { NDPI_PROTOCOL_IPP, ND_PROTO_IPP },
    { NDPI_PROTOCOL_IP_SCTP, ND_PROTO_IP_SCTP },
    { NDPI_PROTOCOL_IP_VRRP, ND_PROTO_IP_VRRP },
    { NDPI_PROTOCOL_IRC, ND_PROTO_IRC },
    { NDPI_PROTOCOL_JABBER, ND_PROTO_XMPP },
    { NDPI_PROTOCOL_KAKAOTALK_VOICE, ND_PROTO_KAKAOTALK_VOICE },
    { NDPI_PROTOCOL_KERBEROS, ND_PROTO_KERBEROS },
    { NDPI_PROTOCOL_KONTIKI, ND_PROTO_KONTIKI },
    { NDPI_PROTOCOL_LDAP, ND_PROTO_LDAP },
    { NDPI_PROTOCOL_LISP, ND_PROTO_LISP },
    { NDPI_PROTOCOL_LLMNR, ND_PROTO_LLMNR },
    { NDPI_PROTOCOL_LOTUS_NOTES, ND_PROTO_LOTUS_NOTES },
    { NDPI_PROTOCOL_MAIL_IMAP, ND_PROTO_MAIL_IMAP },
    { NDPI_PROTOCOL_MAIL_IMAPS, ND_PROTO_MAIL_IMAPS },
    { NDPI_PROTOCOL_MAIL_POP, ND_PROTO_MAIL_POP },
    { NDPI_PROTOCOL_MAIL_POPS, ND_PROTO_MAIL_POPS },
    { NDPI_PROTOCOL_MAIL_SMTP, ND_PROTO_MAIL_SMTP },
    { NDPI_PROTOCOL_MAIL_SMTPS, ND_PROTO_MAIL_SMTPS },
    { NDPI_PROTOCOL_MAPLESTORY, ND_PROTO_MAPLESTORY },
    { NDPI_PROTOCOL_MDNS, ND_PROTO_MDNS },
    { NDPI_PROTOCOL_MEGACO, ND_PROTO_MEGACO },
    { NDPI_PROTOCOL_MEMCACHED, ND_PROTO_MEMCACHED },
    { NDPI_PROTOCOL_MGCP, ND_PROTO_MGCP },
    { NDPI_PROTOCOL_MINING, ND_PROTO_MINING },
    { NDPI_PROTOCOL_MODBUS, ND_PROTO_MODBUS },
    { NDPI_PROTOCOL_MONGODB, ND_PROTO_MONGODB },
    { NDPI_PROTOCOL_MPEGTS, ND_PROTO_MPEGTS },
    { NDPI_PROTOCOL_MQTT, ND_PROTO_MQTT },
    { NDPI_PROTOCOL_MSSQL_TDS, ND_PROTO_MSSQL_TDS },
    { NDPI_PROTOCOL_MYSQL, ND_PROTO_MYSQL },
    { NDPI_PROTOCOL_NATS, ND_PROTO_NATS },
    { NDPI_PROTOCOL_NEST_LOG_SINK, ND_PROTO_NEST_LOG_SINK },
    { NDPI_PROTOCOL_NETBIOS, ND_PROTO_NETBIOS },
    { NDPI_PROTOCOL_NETFLOW, ND_PROTO_NETFLOW },
    { NDPI_PROTOCOL_NFS, ND_PROTO_NFS },
    { NDPI_PROTOCOL_NINTENDO, ND_PROTO_NINTENDO },
    { NDPI_PROTOCOL_NOE, ND_PROTO_NOE },
    { NDPI_PROTOCOL_NTP, ND_PROTO_NTP },
    { NDPI_PROTOCOL_OOKLA, ND_PROTO_OOKLA },
    { NDPI_PROTOCOL_OPENFT, ND_PROTO_OPENFT },
    { NDPI_PROTOCOL_OPENVPN, ND_PROTO_OPENVPN },
    { NDPI_PROTOCOL_ORACLE, ND_PROTO_ORACLE },
    { NDPI_PROTOCOL_POSTGRES, ND_PROTO_POSTGRES },
    { NDPI_PROTOCOL_PPSTREAM, ND_PROTO_PPSTREAM },
    { NDPI_PROTOCOL_PPTP, ND_PROTO_PPTP },
    { NDPI_PROTOCOL_QQLIVE, ND_PROTO_QQLIVE },
    { NDPI_PROTOCOL_QQ, ND_PROTO_QQ },
    { NDPI_PROTOCOL_QUIC, ND_PROTO_QUIC },
    { NDPI_PROTOCOL_RADIUS, ND_PROTO_RADIUS },
    { NDPI_PROTOCOL_RDP, ND_PROTO_RDP },
    { NDPI_PROTOCOL_REDIS, ND_PROTO_REDIS },
    { NDPI_PROTOCOL_REMOTE_SCAN, ND_PROTO_REMOTE_SCAN },
    { NDPI_PROTOCOL_RPC, ND_PROTO_RPC },
    { NDPI_PROTOCOL_RSYNC, ND_PROTO_RSYNC },
    { NDPI_PROTOCOL_RTCP, ND_PROTO_RTCP },
    { NDPI_PROTOCOL_RTMP, ND_PROTO_RTMP },
    { NDPI_PROTOCOL_RTP, ND_PROTO_RTP },
    { NDPI_PROTOCOL_RTSP, ND_PROTO_RTSP },
    { NDPI_PROTOCOL_RX, ND_PROTO_RX },
    { NDPI_PROTOCOL_S7COMM, ND_PROTO_S7COMM },
    { NDPI_PROTOCOL_SAP, ND_PROTO_SAP },
    { NDPI_PROTOCOL_SFLOW, ND_PROTO_SFLOW },
    { NDPI_PROTOCOL_SHOUTCAST, ND_PROTO_SHOUTCAST },
    { NDPI_PROTOCOL_SIGNAL, ND_PROTO_SIGNAL },
    { NDPI_PROTOCOL_SIP, ND_PROTO_SIP },
    { NDPI_PROTOCOL_SKINNY, ND_PROTO_CISCO_SKINNY },
    { NDPI_PROTOCOL_SKYPE_CALL, ND_PROTO_SKYPE_CALL },
    { NDPI_PROTOCOL_SKYPE_TEAMS, ND_PROTO_SKYPE_TEAMS },
    { NDPI_PROTOCOL_SMBV1, ND_PROTO_SMBV1 },
    { NDPI_PROTOCOL_SMBV23, ND_PROTO_SMBV23 },
    { NDPI_PROTOCOL_SMPP, ND_PROTO_SMPP },
    { NDPI_PROTOCOL_SNAPCHAT_CALL, ND_PROTO_SNAPCHAT_CALL },
    { NDPI_PROTOCOL_SNMP, ND_PROTO_SNMP },
    { NDPI_PROTOCOL_SOAP, ND_PROTO_SOAP },
    { NDPI_PROTOCOL_SOCKS, ND_PROTO_SOCKS },
    { NDPI_PROTOCOL_SOMEIP, ND_PROTO_SOMEIP },
    { NDPI_PROTOCOL_SOPCAST, ND_PROTO_SOPCAST },
    { NDPI_PROTOCOL_SPOTIFY, ND_PROTO_SPOTIFY },
    { NDPI_PROTOCOL_SSDP, ND_PROTO_SSDP },
    { NDPI_PROTOCOL_SSH, ND_PROTO_SSH },
    { NDPI_PROTOCOL_STARCRAFT, ND_PROTO_STARCRAFT },
    { NDPI_PROTOCOL_STEALTHNET, ND_PROTO_STEALTHNET },
    { NDPI_PROTOCOL_STEAM, ND_PROTO_STEAM },
    { NDPI_PROTOCOL_STUN, ND_PROTO_STUN },
    { NDPI_PROTOCOL_SYSLOG, ND_PROTO_SYSLOG },
    { NDPI_PROTOCOL_TARGUS_GETDATA, ND_PROTO_TARGUS_GETDATA },
    { NDPI_PROTOCOL_TEAMSPEAK, ND_PROTO_TEAMSPEAK },
    { NDPI_PROTOCOL_TEAMVIEWER, ND_PROTO_TEAMVIEWER },
    { NDPI_PROTOCOL_TELEGRAM, ND_PROTO_TELEGRAM },
    { NDPI_PROTOCOL_TELNET, ND_PROTO_TELNET },
    { NDPI_PROTOCOL_TEREDO, ND_PROTO_TEREDO },
    { NDPI_PROTOCOL_TFTP, ND_PROTO_TFTP },
    { NDPI_PROTOCOL_THUNDER, ND_PROTO_THUNDER },
    { NDPI_PROTOCOL_TIKTOK, ND_PROTO_TIKTOK },
    { NDPI_PROTOCOL_TINC, ND_PROTO_TINC },
    { NDPI_PROTOCOL_TLS, ND_PROTO_TLS },
    { NDPI_PROTOCOL_TOR, ND_PROTO_TOR },
    { NDPI_PROTOCOL_TRUPHONE, ND_PROTO_TRUPHONE },
    { NDPI_PROTOCOL_TVUPLAYER, ND_PROTO_TVUPLAYER },
    { NDPI_PROTOCOL_UBNTAC2, ND_PROTO_UBNTAC2 },
    { NDPI_PROTOCOL_UNKNOWN, ND_PROTO_UNKNOWN },
    { NDPI_PROTOCOL_USENET, ND_PROTO_NNTP },
    { NDPI_PROTOCOL_VHUA, ND_PROTO_VHUA },
    { NDPI_PROTOCOL_VIBER, ND_PROTO_VIBER },
    { NDPI_PROTOCOL_VMWARE, ND_PROTO_VMWARE },
    { NDPI_PROTOCOL_VNC, ND_PROTO_VNC },
    { NDPI_PROTOCOL_VXLAN, ND_PROTO_VXLAN },
    { NDPI_PROTOCOL_WARCRAFT3, ND_PROTO_WARCRAFT3 },
    { NDPI_PROTOCOL_WHATSAPP_CALL, ND_PROTO_WHATSAPP_CALL },
    { NDPI_PROTOCOL_WHATSAPP, ND_PROTO_WHATSAPP },
    { NDPI_PROTOCOL_WHOIS_DAS, ND_PROTO_WHOIS_DAS },
    { NDPI_PROTOCOL_WIREGUARD, ND_PROTO_WIREGUARD },
    { NDPI_PROTOCOL_WORLD_OF_KUNG_FU, ND_PROTO_WORLDOFKUNGFU },
    { NDPI_PROTOCOL_WORLDOFWARCRAFT, ND_PROTO_WORLDOFWARCRAFT },
    { NDPI_PROTOCOL_WSD, ND_PROTO_WSD },
    { NDPI_PROTOCOL_XBOX, ND_PROTO_XBOX },
    { NDPI_PROTOCOL_XDMCP, ND_PROTO_XDMCP },
    { NDPI_PROTOCOL_YAHOO, ND_PROTO_YAHOO },
    { NDPI_PROTOCOL_ZATTOO, ND_PROTO_ZATTOO },
    { NDPI_PROTOCOL_ZMQ, ND_PROTO_ZMQ },
    { NDPI_PROTOCOL_ZOOM, ND_PROTO_ZOOM },
};

typedef unordered_map<uint16_t, vector<pair<uint16_t, nd_proto_id_t>>> nd_ndpi_portmap_t;

const nd_ndpi_portmap_t nd_ndpi_portmap = {
    { NDPI_PROTOCOL_TLS, {
        { 53, ND_PROTO_DOT },
        { 443, ND_PROTO_HTTPS },
        { 563, ND_PROTO_NNTPS },
        { 853, ND_PROTO_DOT },
        { 989, ND_PROTO_FTPS_DATA },
        { 990, ND_PROTO_FTPS_CONTROL },
        { 5061, ND_PROTO_SIPS },
        { 6697, ND_PROTO_IRCS },
        { 8883, ND_PROTO_MQTTS },
    } },
};

class ndFlow;
const nd_proto_id_t nd_ndpi_proto_find(uint16_t id, const ndFlow *flow);

#endif // _ND_PROTOS_H
// vi: expandtab shiftwidth=4 softtabstop=4 tabstop=4
