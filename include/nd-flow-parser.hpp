// Netify Agent
// Copyright (C) 2015-2023 eGloo Incorporated
// <http://www.egloo.ca>
//
// This program is free software: you can redistribute it
// and/or modify it under the terms of the GNU General
// Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your
// option) any later version.
//
// This program is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program.  If not, see
// <http://www.gnu.org/licenses/>.

#pragma once

#define _NDFP_MAX_BUFLEN        256

#define _NDFP_OTHER_UNKNOWN     0
#define _NDFP_OTHER_UNSUPPORTED 1
#define _NDFP_OTHER_LOCAL       2
#define _NDFP_OTHER_MULTICAST   3
#define _NDFP_OTHER_BROADCAST   4
#define _NDFP_OTHER_REMOTE      5
#define _NDFP_OTHER_ERROR       6

#define _NDFP_TUNNEL_NONE       0
#define _NDFP_TUNNEL_GTP        1

#define _NDFP_ORIGIN_UNKNOWN    0
#define _NDFP_ORIGIN_LOCAL      1
#define _NDFP_ORIGIN_OTHER      2

#define _NDFP_flow \
    ((ndFlowParser *)yyget_extra(scanner))->flow
#define _NDFP_local_mac \
    ((ndFlowParser *)yyget_extra(scanner))->local_mac
#define _NDFP_other_mac \
    ((ndFlowParser *)yyget_extra(scanner))->other_mac
#define _NDFP_local_ip \
    ((ndFlowParser *)yyget_extra(scanner))->local_ip
#define _NDFP_other_ip \
    ((ndFlowParser *)yyget_extra(scanner))->other_ip
#define _NDFP_local_port \
    ((ndFlowParser *)yyget_extra(scanner))->local_port
#define _NDFP_other_port \
    ((ndFlowParser *)yyget_extra(scanner))->other_port
#define _NDFP_origin \
    ((ndFlowParser *)yyget_extra(scanner))->origin
#define _NDFP_result \
    ((ndFlowParser *)yyget_extra(scanner))->expr_result
#define _NDFP_categories \
    ((ndFlowParser *)yyget_extra(scanner))->ndi.categories

#if 0
#define _NDFP_debugf(f, ...) nd_dprintf(f, __VA_ARGS__)
#else
#define _NDFP_debugf(f, ...) \
    do { \
    } \
    while (0)
#endif

#if defined __cplusplus

#include <cstdint>
#include <string>

#include "nd-flow.hpp"
#include "nd-instance.hpp"

using namespace std;

class ndFlowParser : public ndInstanceClient
{
public:
    ndFlowParser();
    virtual ~ndFlowParser();

    bool Parse(nd_flow_ptr const &flow, const string &expr);

    nd_flow_ptr flow;
    const char *local_mac;
    const char *other_mac;
    const ndAddr *local_ip;
    const ndAddr *other_ip;
    uint16_t local_port;
    uint16_t other_port;
    uint16_t origin;

    bool expr_result;

protected:
    void *scanner;
};

#endif
