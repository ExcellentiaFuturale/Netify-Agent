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

#ifdef HAVE_CONFIG_H
#include "config.h"
#ifndef PACKAGE_VERSION
#error "PACKAGE_VERSION not defined"
#endif
#endif

#include <atomic>
#include <csignal>

#include "nd-apps.hpp"
#include "nd-category.hpp"
#include "nd-config.hpp"
#include "nd-dhc.hpp"
#include "nd-except.hpp"
#include "nd-fhc.hpp"
#include "nd-flow-map.hpp"
#include "nd-napi.hpp"
#include "nd-packet.hpp"
#include "nd-plugin.hpp"
#include "nd-protos.hpp"
#include "nd-serializer.hpp"
#include "nd-signal.hpp"
#include "nd-thread.hpp"
#include "nd-util.hpp"

#ifdef _ND_USE_CONNTRACK
#include "nd-conntrack.hpp"
#endif

#ifdef _ND_USE_NETLINK
#include "nd-netlink.hpp"
#endif

using namespace std;

class ndInstanceStatus : public ndSerializer {
 public:
  ndInstanceStatus();

  long cpus;
  struct timespec ts_epoch;
  struct timespec ts_now;
  atomic<size_t> flows;
  size_t flows_prev;
  size_t flows_purged;
  size_t flows_expiring;
  size_t flows_expired;
  size_t flows_active;
  size_t flows_in_use;
  double cpu_user;
  double cpu_user_prev;
  double cpu_system;
  double cpu_system_prev;
  size_t maxrss_kb;
  size_t maxrss_kb_prev;
#if (defined(_ND_USE_LIBTCMALLOC) && \
     defined(HAVE_GPERFTOOLS_MALLOC_EXTENSION_H))
  size_t tcm_alloc_kb;
  size_t tcm_alloc_kb_prev;
#endif
  bool dhc_status;
  size_t dhc_size;

  template <class T>
  void Encode(T &output) const {
    serialize(output, {"timestamp"}, time(NULL));
    serialize(output, {"update_interval"},
              ndGC.update_interval);
    serialize(output, {"update_imf"}, ndGC.update_imf);
    serialize(output, {"uptime"},
              unsigned(ts_now.tv_sec - ts_epoch.tv_sec));
    serialize(output, {"cpu_cores"}, (unsigned)cpus);
    serialize(output, {"cpu_user"}, cpu_user);
    serialize(output, {"cpu_user_prev"}, cpu_user_prev);
    serialize(output, {"cpu_system"}, cpu_system);
    serialize(output, {"cpu_system_prev"}, cpu_system_prev);
    serialize(output, {"flow_count"}, flows.load());
    serialize(output, {"flow_count_prev"}, flows_prev);
    serialize(output, {"flows_purged"}, flows_purged);
    serialize(output, {"flows_expiring"}, flows_expiring);
    serialize(output, {"flows_expired"}, flows_expired);
    serialize(output, {"flows_active"}, flows_active);
    serialize(output, {"flows_in_use"}, flows_in_use);
    serialize(output, {"maxrss_kb"}, maxrss_kb);
    serialize(output, {"maxrss_kb_prev"}, maxrss_kb_prev);
#if (defined(_ND_USE_LIBTCMALLOC) && \
     defined(HAVE_GPERFTOOLS_MALLOC_EXTENSION_H))
    serialize(output, {"tcm_kb"}, (unsigned)tcm_alloc_kb);
    serialize(output, {"tcm_kb_prev"},
              (unsigned)tcm_alloc_kb_prev);
#endif  // _ND_USE_LIBTCMALLOC
    serialize(output, {"dhc_status"}, dhc_status);
    if (dhc_status)
      serialize(output, {"dhc_size"}, dhc_size);
  }
};

class ndCaptureThread;
class ndDetectionThread;
class ndNetifyApiManager;
#ifdef _ND_USE_CONNTRACK
class ndConntrackThread;
#endif

typedef map<int16_t, ndDetectionThread *>
    nd_detection_threads;
typedef map<string, vector<ndCaptureThread *>>
    nd_capture_threads;
typedef map<string, pair<uint8_t, ndPacketStats>>
    nd_interface_stats;

class ndInstance : public ndThread, public ndSerializer {
 public:
  static ndInstance &Create(
      const string &tag = "nd-instance");

  static void Destroy(void);

  ndInstance() = delete;
  ndInstance(const ndInstance &) = delete;
  ndInstance &operator=(const ndInstance &) = delete;

  static inline ndInstance &GetInstance() {
    if (instance == nullptr) {
      throw ndSystemException(__PRETTY_FUNCTION__,
                              "instance not found", ENOENT);
    }
    return *instance;
  }

  static void InitializeSignals(sigset_t &sigset,
                                bool minimal = false);

  enum ndConfigResult {
    ndCR_OK,
    ndCR_AGENT_STATUS,
    ndCR_DISABLED_OPTION,
    ndCR_DUMP_LIST,
    ndCR_EXPORT_APPS,
    ndCR_FORCE_RESULT,
    ndCR_GENERATE_UUID,
    ndCR_HASH_TEST,
    ndCR_INVALID_INTERFACE,
    ndCR_INVALID_INTERFACES,
    ndCR_INVALID_OPTION,
    ndCR_INVALID_PERMS,
    ndCR_INVALID_VALUE,
    ndCR_LIBCURL_FAILURE,
    ndCR_LOAD_FAILURE,
    ndCR_LOOKUP_ADDR,
    ndCR_PROVISION_UUID,
    ndCR_SAVE_UUID_FAILURE,
    ndCR_SET_CONFIG,
    ndCR_USAGE_OR_VERSION,
  };

#define ndCR_Pack(r, c) ((c << 16) + (r & 0x0000ffff))
#define ndCR_Code(c) ((c & 0xffff0000) >> 16)
#define ndCR_Result(r) (r & 0x0000ffff)

  uint32_t InitializeConfig(int argc, char *const argv[]);

  bool InitializeTimers(
      int sig_update = ND_SIG_UPDATE,
      int sig_update_napi = ND_SIG_UPDATE_NAPI);

  bool Daemonize(void);

  enum ndDumpFlags {
    ndDUMP_NONE = 0x00,
    ndDUMP_TYPE_PROTOS = 0x01,
    ndDUMP_TYPE_APPS = 0x02,
    ndDUMP_TYPE_CAT_APP = 0x04,
    ndDUMP_TYPE_CAT_PROTO = 0x08,
    ndDUMP_TYPE_RISKS = 0x10,
    ndDUMP_TYPE_VALID = 0x20,
    ndDUMP_SORT_BY_TAG = 0x40,
    ndDUMP_WITH_CATS = 0x80,
    ndDUMP_TYPE_CATS =
        (ndDUMP_TYPE_CAT_APP | ndDUMP_TYPE_CAT_PROTO),
    ndDUMP_TYPE_ALL =
        (ndDUMP_TYPE_PROTOS | ndDUMP_TYPE_APPS)
  };

  template <class T>
  void Encode(T &output) const {
    serialize(output, {"build_version"},
              nd_get_version_and_features());
    serialize(output, {"agent_version"},
              strtod(PACKAGE_VERSION, NULL));
    serialize(
        output, {"json_version"},
        1.9  // XXX: Deprecated, keep for compatibility
    );
  }

  bool SetConfigOption(int option, const string &arg);

  bool DumpList(uint8_t type = ndDUMP_TYPE_ALL);

  bool LookupAddress(const string &ip);

  void CommandLineHelp(bool version_only = false);

  bool AddInterface(const string &ifname,
                    nd_interface_role role, unsigned type);

  bool CheckAgentUUID(void);

  bool SaveAgentStatus(const nd_interface_stats &stats);
  bool DisplayAgentStatus(void);

  int Run(void);

  void Terminate(void) {
    if (ShouldTerminate()) {
      nd_dprintf("%s: Forcing termination...\n",
                 tag.c_str());
      terminate_force = true;
    }
    ndThread::Terminate();
  }

  inline const string &GetVersion() const {
    return version;
  }
  inline const ndInstanceStatus &GetStatus() const {
    return status;
  }

  template <class T>
  void EncodeApplications(T &output) {
    nd_apps_t entries;
    apps.Get(entries);
    for (auto &app : entries) {
      T jo;

      jo["id"] = app.second;
      jo["tag"] = app.first;

      output.push_back(jo);
    }
  };
  template <class T>
  void EncodeProtocols(T &output) const {
    for (auto &proto : nd_protos) {
      T jo;

      jo["id"] = proto.first;
      jo["tag"] = proto.second;

      output.push_back(jo);
    }
  };

  enum ndIPCMessage {
    ndIPC_NONE,
    ndIPC_NETLINK_IO,
    ndIPC_RELOAD,
    ndIPC_TERMINATE,
    ndIPC_UPDATE,
    ndIPC_UPDATE_NAPI,
  };

  inline void SendIPC(enum ndIPCMessage id) {
    ndThread::SendIPC((uint32_t)id);
  }
  inline bool SendSignal(const siginfo_t &si) {
    switch (si.si_signo) {
#ifdef _ND_USE_NETLINK
      case SIGIO:
        if (ndGC_USE_NETLINK && netlink != nullptr &&
            netlink->GetDescriptor() == si.si_fd) {
          ndThread::SendIPC((uint32_t)ndIPC_NETLINK_IO);
          return true;
        }
        break;
#endif
      case SIGHUP:
        ndThread::SendIPC((uint32_t)ndIPC_RELOAD);
        return true;
      case SIGINT:
      case SIGTERM:
#ifdef SIGPWR
      case SIGPWR:
#endif
        ndThread::SendIPC((uint32_t)ndIPC_TERMINATE);
        return true;
      default:
        if (timer_update.GetSignal() >= 0 &&
            si.si_signo == timer_update.GetSignal()) {
          ndThread::SendIPC((uint32_t)ndIPC_UPDATE);
          return true;
        } else if (timer_update_napi.GetSignal() >= 0 &&
                   si.si_signo ==
                       timer_update_napi.GetSignal()) {
          ndThread::SendIPC((uint32_t)ndIPC_UPDATE_NAPI);
          return true;
        }
        break;
    }
    return false;
  }

  int exit_code;

  ndInstanceStatus status;
  ndPacketStats pkt_stats_global;
  ndApplications apps;
  ndCategories categories;
  ndDomains domains;
  ndInterfaces interfaces;
  ndAddrType addr_types;
  ndDNSHintCache *dns_hint_cache;
  ndFlowHashCache *flow_hash_cache;
  ndFlowMap *flow_buckets;
#ifdef _ND_USE_NETLINK
  ndNetlink *netlink;
#endif
  ndNetifyApiManager api_manager;
#ifdef _ND_USE_CONNTRACK
  ndConntrackThread *thread_conntrack;
#endif
  nd_detection_threads thread_detection;
  ndPluginManager plugins;

 protected:
  friend class ndInstanceThread;

  static ndInstance *instance;

  void *Entry(void);

  bool Reload(bool broadcast = true);

  void CreateCaptureInterfaces(ndInterfaces &ifaces);

  bool CreateCaptureThreads(ndInterfaces &ifaces,
                            nd_capture_threads &threads);
  void DestroyCaptureThreads(nd_capture_threads &threads,
                             bool expire_flows = false);
  size_t ReapCaptureThreads(nd_capture_threads &threads);
  bool ReloadCaptureThreads(nd_capture_threads &threads);

  int WaitForIPC(int timeout = -1);

  void UpdateStatus(void);

  void DisplayDebugScoreboard(void);

  bool ExpireFlow(nd_flow_ptr &flow);

  void ProcessUpdate(nd_capture_threads &threads);

  void ProcessFlows(void);

  ndTimer timer_update, timer_update_napi;

  string tag;
  string self;
  pid_t self_pid;
  string version;

  atomic_bool terminate_force;

  string conf_filename;

 private:
  ndInstance(const string &tag = "nd-instance");
  virtual ~ndInstance();
};

class ndInstanceClient {
 public:
  ndInstanceClient() : ndi(ndInstance::GetInstance()) {}

  ndInstance &ndi;
};
