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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef _ND_UTIL_H
#define _ND_UTIL_H

#include <sys/socket.h>
#include <sys/stat.h>

#include <cstddef>
#include <ctime>
#include <map>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

#define ND_SHA1_BUFFER 4096

#define ND_C_RESET "\033[0m"
#define ND_C_RED "\033[0;31m"
#define ND_C_GREEN "\033[0;32m"
#define ND_C_YELLOW "\033[0;33m"

#define ND_I_INFO "•"
#define ND_I_OK "✓"
#define ND_I_WARN "!"
#define ND_I_FAIL "✗"
#define ND_I_NOTE "↪"
#define ND_I_RARROW "→"

void *nd_mem_alloc(size_t size);

void nd_mem_free(void *ptr);

#ifndef __FreeBSD__
class ndLogBuffer : public streambuf {
 public:
  int overflow(int ch = EOF);
  virtual int sync();

 protected:
  ostringstream os;
};

class ndDebugLogBuffer : public ndLogBuffer {
 public:
  virtual int sync();
};

class ndDebugLogBufferUnlocked : public ndLogBuffer {
 public:
  virtual int sync();
};

class ndDebugLogBufferFlow : public ndLogBuffer {
 public:
  virtual int sync();
};

class ndLogStream : public ostream {
 public:
  ndLogStream() : ostream(new ndLogBuffer) {}

  virtual ~ndLogStream() { delete rdbuf(); }
};

class ndDebugLogStream : public ostream {
 public:
  enum Type {
    DLT_NONE,
    DLT_UNLOCKED,
    DLT_FLOW,
  };

  ndDebugLogStream(Type type = DLT_NONE)
      : ostream(
            (type == DLT_NONE)
                ? (streambuf *)new ndDebugLogBuffer
                : ((type == DLT_UNLOCKED)
                       ? (streambuf
                              *)new ndDebugLogBufferUnlocked
                       : (streambuf
                              *)new ndDebugLogBufferFlow)) {
  }

  virtual ~ndDebugLogStream() { delete rdbuf(); }
};
#endif

void nd_output_lock(void);
void nd_output_unlock(void);

void nd_printf(const char *format, ...);
void nd_printf(const char *format, va_list ap);
void nd_dprintf(const char *format, ...);
void nd_dprintf(const char *format, va_list ap);
void nd_flow_printf(const char *format, ...);

#ifdef NDPI_ENABLE_DEBUG_MESSAGES
void nd_ndpi_debug_printf(uint32_t protocol, void *ndpi,
                          ndpi_log_level_t level,
                          const char *file,
                          const char *func, unsigned line,
                          const char *format, ...);
#endif

void nd_print_address(const struct sockaddr_storage *addr);

void nd_print_binary(uint32_t byte);

void nd_print_number(ostringstream &os, uint64_t value,
                     bool units_binary = true);
void nd_print_percent(ostringstream &os,
                      const double &value);

void nd_ltrim(string &s, unsigned char c = 0);
void nd_rtrim(string &s, unsigned char c = 0);
void nd_trim(string &s, unsigned char c = 0);

int nd_sha1_file(const string &filename, uint8_t *digest);

void nd_sha1_to_string(const uint8_t *digest_bin,
                       string &digest_str);
void nd_sha1_to_string(const vector<uint8_t> &digest_bin,
                       string &digest_str);

bool nd_string_to_mac(const string &src, uint8_t *mac);
sa_family_t nd_string_to_ip(const string &src,
                            sockaddr_storage *ip);
bool nd_ip_to_string(sa_family_t af, const void *addr,
                     string &dst);
bool nd_ip_to_string(const sockaddr_storage &ip,
                     string &dst);

bool nd_is_ipaddr(const char *ip);

void nd_private_ipaddr(uint8_t index,
                       struct sockaddr_storage &addr);

bool nd_load_uuid(string &uuid, const string &path,
                  size_t length);
bool nd_save_uuid(const string &uuid, const string &path,
                  size_t length);

void nd_seed_rng(void);

void nd_generate_uuid(string &uuid);

inline const char *nd_get_version(void) {
  return PACKAGE_VERSION;
};
const string &nd_get_version_and_features(void);

bool nd_parse_app_tag(const string &tag, unsigned &id,
                      string &name);

int nd_touch(const string &filename);

int nd_file_load(const string &filename, string &data);

void nd_file_save(const string &filename,
                  const string &data, bool append = false,
                  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP,
                  const char *user = NULL,
                  const char *group = NULL);

int nd_ifreq(const string &name, unsigned long request,
             struct ifreq *ifr);

void nd_basename(const string &path, string &base);

pid_t nd_is_running(pid_t pid, const string &exe_base);
pid_t nd_load_pid(const string &pidfile);
int nd_save_pid(const string &pidfile, pid_t pid);

int nd_file_exists(const string &path);
int nd_dir_exists(const string &path);

void nd_uptime(time_t ut, string &uptime);

int nd_functions_exec(const string &func, const string &arg,
                      string &output);

void nd_os_detect(string &os);

#define _ND_LOG_FILE_STAMP "%Y%m%d-%H%M%S"
#define _ND_LOG_FILE_STAMP_SIZE sizeof("YYYYMMDD-HHMMSS")

class ndLogDirectory {
 public:
  ndLogDirectory(const string &path, const string &prefix,
                 const string &suffix,
                 bool overwrite = false);
  virtual ~ndLogDirectory();

  FILE *Open(const string &ext = "");
  void Close(void);
  void Discard(void);

 protected:
  string path;
  string prefix;
  string suffix;

  bool overwrite;

  FILE *hf_cur;
  string filename;
};

void nd_regex_error(const regex_error &e, string &error);

bool nd_scan_dotd(const string &path,
                  vector<string> &files);

void nd_set_hostname(string &dst, const char *src,
                     size_t length, bool strict = true);
void nd_set_hostname(char *dst, const char *src,
                     size_t length, bool strict = true);

void nd_expand_variables(const string &input,
                         string &output,
                         map<string, string> &vars);

void nd_gz_deflate(size_t length, const uint8_t *data,
                   vector<uint8_t> &output);

class ndTimer {
 public:
  ndTimer(void) : sig(-1), valid(false), id(nullptr) {}
  virtual ~ndTimer() { Reset(); }

  void Create(int sig);
  void Reset(void);

  void Set(const struct itimerspec &itspec);

  inline bool IsValid(void) const { return valid; }
  inline int GetSignal(void) const { return sig; }

 protected:
  int sig;
  bool valid;
  timer_t id;
};

void nd_get_ip_protocol_name(int protocol, string &result);

int nd_glob(const string &pattern, vector<string> &results);

time_t nd_time_monotonic(void);

void nd_tmpfile(const string &prefix, string &filename);

bool nd_copy_file(const string &src, const string &dst);

#endif  // _ND_UTIL_H
