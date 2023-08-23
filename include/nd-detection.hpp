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

#ifndef _ND_DETECTION_THREAD_H
#define _ND_DETECTION_THREAD_H

#include "nd-except.hpp"
#include "nd-flow-parser.hpp"

class ndSocketThread;

class ndDetectionThreadException : public runtime_error {
 public:
  explicit ndDetectionThreadException(
      const string &what_arg)
      : runtime_error(what_arg) {}
};

class ndDetectionQueueEntry {
 public:
  ndDetectionQueueEntry(nd_flow_ptr &flow,
                        const ndPacket *packet,
                        const uint8_t *data,
                        uint16_t length)
      : packet(packet),
        flow(flow),
        data(data),
        length(length) {}

  virtual ~ndDetectionQueueEntry() {
    if (packet != nullptr) delete packet;
  }

  const ndPacket *packet;
  nd_flow_ptr flow;
  const uint8_t *data;
  uint16_t length;
};

class ndDetectionThread : public ndThread,
                          public ndInstanceClient {
 public:
  ndDetectionThread(int16_t cpu, const string &tag,
#ifdef _ND_USE_NETLINK
                    ndNetlink *netlink,
#endif
#ifdef _ND_USE_CONNTRACK
                    ndConntrackThread *thread_conntrack,
#endif
                    ndDNSHintCache *dhc = NULL,
                    ndFlowHashCache *fhc = NULL,
                    uint8_t private_addr = 0);

  virtual ~ndDetectionThread();

  // XXX: Not thread-safe!  Lock before calling...
  virtual void Reload(void);

  void QueuePacket(nd_flow_ptr &flow,
                   const ndPacket *packet = nullptr,
                   const uint8_t *data = nullptr,
                   uint16_t length = 0);

  struct ndpi_detection_module_struct *GetDetectionModule(
      void) {
    return ndpi;
  }

  virtual void *Entry(void);

 protected:
#ifdef _ND_USE_NETLINK
  ndNetlink *netlink;
#endif
#ifdef _ND_USE_CONNTRACK
  ndConntrackThread *thread_conntrack;
#endif
  struct ndpi_detection_module_struct *ndpi;

  ndAddr::PrivatePair private_addrs;

  ndDNSHintCache *dhc;
  ndFlowHashCache *fhc;

  string flow_digest, flow_digest_mdata;

  queue<ndDetectionQueueEntry *> pkt_queue;
  pthread_cond_t pkt_queue_cond;
  pthread_mutex_t pkt_queue_cond_mutex;

  size_t flows;

  ndFlowParser parser;

  void ProcessPacketQueue(void);
  void ProcessPacket(ndDetectionQueueEntry *entry);
  bool ProcessALPN(ndDetectionQueueEntry *entry,
                   bool client = true);
  void ProcessFlow(ndDetectionQueueEntry *entry);

  void SetDetectedApplication(ndDetectionQueueEntry *entry,
                              nd_app_id_t app_id);
  void SetGuessedProtocol(ndDetectionQueueEntry *entry);

  void FlowUpdate(ndDetectionQueueEntry *entry);
};

#endif  // _ND_DETECTION_THREAD_H
