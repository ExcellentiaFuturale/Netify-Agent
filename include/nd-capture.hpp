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

#include "nd-except.hpp"
#include "nd-instance.hpp"
#include "nd-thread.hpp"

class ndCaptureThreadException : public runtime_error
{
public:
    explicit ndCaptureThreadException(const string &what_arg)
      : runtime_error(what_arg) { }
};

class ndCaptureThread : public ndThread, public ndInstanceClient
{
public:
    ndCaptureThread(unsigned cs_type, int16_t cpu,
      nd_iface_ptr &iface, const nd_detection_threads &threads_dpi,
      ndDNSHintCache *dhc = NULL, uint8_t private_addr = 0);

    virtual ~ndCaptureThread() { }

    virtual void *Entry(void) = 0;

    // XXX: Ensure thread is locked before calling!
    virtual void GetCaptureStats(ndPacketStats &stats) {
        this->stats.AddAndReset(stats);
    }

    enum nd_capture_states {
        STATE_INIT,
        STATE_ONLINE,
        STATE_OFFLINE,
    };

    atomic_uchar capture_state;

protected:
    int dl_type;
    unsigned cs_type;

    nd_iface_ptr iface;
    ndFlow flow;

    time_t tv_epoch;
    uint64_t ts_pkt_first;
    uint64_t ts_pkt_last;

    ndAddr::PrivatePair private_addrs;

    ndPacketStats stats;

    string flow_digest;

    ndDNSHintCache *dhc;

    const nd_detection_threads &threads_dpi;
    int16_t dpi_thread_id;

    const ndPacket *ProcessPacket(const ndPacket *packet);

    bool ProcessDNSPacket(nd_flow_ptr &flow,
      const uint8_t *pkt, uint16_t pkt_len, uint16_t proto);
};
