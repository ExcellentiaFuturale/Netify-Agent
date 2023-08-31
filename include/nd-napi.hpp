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

#ifndef _ND_NAPI_H
#define _ND_NAPI_H

#include <curl/curl.h>
#include <unistd.h>

#include <map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include "nd-thread.hpp"

class ndNetifyApiManager;

class ndNetifyApiThread : public ndThread {
 public:
  ndNetifyApiThread();
  virtual ~ndNetifyApiThread();

  virtual void *Entry(void) = 0;

  void AppendContent(const char *data, size_t length) {
    try {
      content.append(data, length);
    } catch (exception &e) {
      throw ndThreadException(e.what());
    }
  }

  void ParseHeader(const string &header_raw);

  enum Method {
    METHOD_GET,
    METHOD_POST,
  };

  typedef map<string, string> Headers;

 protected:
  friend class ndNetifyApiManager;

  void CreateHeaders(const Headers &headers);
  void DestroyHeaders(void);

  void Perform(Method method, const string &url,
               const Headers &headers);

  CURL *ch;
  long http_rc;
  Headers headers_rx;
  struct curl_slist *headers_tx;
  string content;
  string content_type;
};

class ndNetifyApiBootstrap : public ndNetifyApiThread {
 public:
  ndNetifyApiBootstrap() : ndNetifyApiThread() {}

  virtual void *Entry(void);

 protected:
  friend class ndNetifyApiManager;
};

class ndNetifyApiDownload : public ndNetifyApiThread {
 public:
  ndNetifyApiDownload(const string &token,
                      const string &url)
      : ndNetifyApiThread(), token(token), url(url) {}

  virtual ~ndNetifyApiDownload() {
    if (!temp_file.empty()) unlink(temp_file.c_str());
  }

  virtual void *Entry(void);

 protected:
  friend class ndNetifyApiManager;

  string token;
  string url;
  string temp_file;
};

class ndNetifyApiManager {
 public:
  ndNetifyApiManager() {}
  virtual ~ndNetifyApiManager() { Terminate(); }

  bool Update(void);
  void Terminate(void);

 protected:
  enum Request {
    REQUEST_NONE,
    REQUEST_BOOTSTRAP,
    REQUEST_DOWNLOAD_CONFIG,
    REQUEST_DOWNLOAD_CATEGORIES,
  };

  typedef unordered_map<Request, ndNetifyApiThread *>
      Requests;

  Requests requests;

  typedef unordered_map<Request, string> Urls;

  Urls urls;

  string token;

  bool ProcessBootstrapRequest(
      ndNetifyApiBootstrap *bootstrap);
};

#endif  // _ND_NAPI_H
