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

#include "nd-except.hpp"
#include "nd-thread.hpp"
#include "nlohmann/json.hpp"
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "nd-config.hpp"
#include "nd-except.hpp"
#include "nd-napi.hpp"
#include "nd-util.hpp"

static int ndNetifyApiThread_curl_debug(
    CURL *ch __attribute__((unused)), curl_infotype type,
    char *data, size_t size, void *param) {
  string buffer;
  if (!ndGC_DEBUG_CURL) return 0;

  ndThread *thread = reinterpret_cast<ndThread *>(param);

  switch (type) {
    case CURLINFO_TEXT:
      buffer.assign(data, size);
      nd_dprintf("%s: %s", thread->GetTag().c_str(),
                 buffer.c_str());
      break;
    case CURLINFO_HEADER_IN:
      buffer.assign(data, size);
      nd_dprintf("%s: <-- %s", thread->GetTag().c_str(),
                 buffer.c_str());
      break;
    case CURLINFO_HEADER_OUT:
      buffer.assign(data, size);
      nd_dprintf("%s: --> %s", thread->GetTag().c_str(),
                 buffer.c_str());
      break;
    case CURLINFO_DATA_IN:
      nd_dprintf("%s: <-- %lu data bytes\n",
                 thread->GetTag().c_str(), size);
      break;
    case CURLINFO_DATA_OUT:
      nd_dprintf("%s: --> %lu data bytes\n",
                 thread->GetTag().c_str(), size);
      break;
    case CURLINFO_SSL_DATA_IN:
      nd_dprintf("%s: <-- %lu SSL bytes\n",
                 thread->GetTag().c_str(), size);
      break;
    case CURLINFO_SSL_DATA_OUT:
      nd_dprintf("%s: --> %lu SSL bytes\n",
                 thread->GetTag().c_str(), size);
      break;
    default:
      break;
  }

  return 0;
}

static size_t ndNetifyApiThread_read_data(char *data,
                                          size_t size,
                                          size_t nmemb,
                                          void *user) {
  size_t length = size * nmemb;
  ndNetifyApiThread *thread_napi =
      reinterpret_cast<ndNetifyApiThread *>(user);

  thread_napi->AppendContent((const char *)data, length);

  return length;
}

static size_t ndNetifyApiThread_parse_header(char *data,
                                             size_t size,
                                             size_t nmemb,
                                             void *user) {
  size_t length = size * nmemb;

  // size_t ndNetifyApiThread_parse_header(char*, size_t,
  // size_t, void*): HTTP/1.1 200 OK, 1, 17
  // nd_dprintf("%s: %s, %u, %u\n", __PRETTY_FUNCTION__,
  // data, size, nmemb);

  if (size != 1 || length == 0) return 0;

  ndNetifyApiThread *thread_napi =
      reinterpret_cast<ndNetifyApiThread *>(user);

  string header_data;
  header_data.assign(data, length);

  thread_napi->ParseHeader(header_data);

  return length;
}

#if (LIBCURL_VERSION_NUM < 0x073200)
static int ndNetifyApiThread_progress(
    void *user, double dltotal __attribute__((unused)),
    double dlnow __attribute__((unused)),
    double ultotal __attribute__((unused)),
    double ulnow __attribute__((unused)))
#else
static int ndNetifyApiThread_progress(
    void *user, curl_off_t dltotal __attribute__((unused)),
    curl_off_t dlnow __attribute__((unused)),
    curl_off_t ultotal __attribute__((unused)),
    curl_off_t ulnow __attribute__((unused)))
#endif
{
  ndNetifyApiThread *thread_napi =
      reinterpret_cast<ndNetifyApiThread *>(user);

  if (thread_napi->ShouldTerminate()) return 1;

  return 0;
}

ndNetifyApiThread::ndNetifyApiThread()
    : ndThread("netify-api"),
      ch(nullptr),
      http_rc(0),
      headers_tx(nullptr) {
  if ((ch = curl_easy_init()) == nullptr)
    throw ndThreadException("curl_easy_init");

  curl_easy_setopt(ch, CURLOPT_MAXREDIRS, 3);
  curl_easy_setopt(ch, CURLOPT_FOLLOWLOCATION, 1);
  curl_easy_setopt(ch, CURLOPT_CONNECTTIMEOUT, 20);
  curl_easy_setopt(ch, CURLOPT_TIMEOUT, 60);
  curl_easy_setopt(ch, CURLOPT_NOSIGNAL, 1);

  curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION,
                   ndNetifyApiThread_read_data);
  curl_easy_setopt(ch, CURLOPT_WRITEDATA,
                   static_cast<void *>(this));

  curl_easy_setopt(ch, CURLOPT_HEADERFUNCTION,
                   ndNetifyApiThread_parse_header);
  curl_easy_setopt(ch, CURLOPT_HEADERDATA,
                   static_cast<void *>(this));

  curl_easy_setopt(ch, CURLOPT_NOPROGRESS, 0);
#if (LIBCURL_VERSION_NUM < 0x073200)
  curl_easy_setopt(ch, CURLOPT_PROGRESSFUNCTION,
                   ndNetifyApiThread_progress);
  curl_easy_setopt(ch, CURLOPT_PROGRESSDATA,
                   static_cast<void *>(this));
#else
  curl_easy_setopt(ch, CURLOPT_XFERINFOFUNCTION,
                   ndNetifyApiThread_progress);
  curl_easy_setopt(ch, CURLOPT_XFERINFODATA,
                   static_cast<void *>(this));
#endif
#ifdef _ND_WITH_LIBCURL_ZLIB
#if (LIBCURL_VERSION_NUM >= 0x072106)
  curl_easy_setopt(ch, CURLOPT_ACCEPT_ENCODING, "gzip");
#endif
#endif  // _ND_WITH_LIBCURL_ZLIB
  if (ndGC_DEBUG_CURL) {
    curl_easy_setopt(ch, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(ch, CURLOPT_DEBUGFUNCTION,
                     ndNetifyApiThread_curl_debug);
    curl_easy_setopt(ch, CURLOPT_DEBUGDATA,
                     static_cast<void *>(this));
  }

  //    curl_easy_setopt(ch, CURLOPT_SSL_VERIFYPEER, 0);
  //    curl_easy_setopt(ch, CURLOPT_SSL_VERIFYHOST, 0);
  //    curl_easy_setopt(ch, CURLOPT_SSLVERSION,
  //    CURL_SSLVERSION_TLSv1);
}

ndNetifyApiThread::~ndNetifyApiThread() {
  Terminate();

  Join();

  if (ch != nullptr) {
    curl_easy_cleanup(ch);
    ch = nullptr;
  }

  DestroyHeaders();
}

void ndNetifyApiThread::ParseHeader(
    const string &header_raw) {
  string key, value;
  size_t p = string::npos;
  if ((p = header_raw.find_first_of(":")) != string::npos) {
    key = header_raw.substr(0, p);
    value = header_raw.substr(p + 1);
  }

  if (!key.empty() && !value.empty()) {
    transform(key.begin(), key.end(), key.begin(),
              [](unsigned char c) { return tolower(c); });

    nd_trim(key);
    nd_trim(value);

    if (headers_rx.find(key) == headers_rx.end()) {
      headers_rx[key] = value;
      if (ndGC_DEBUG_CURL) {
        nd_dprintf("%s: header: %s: %s\n", tag.c_str(),
                   key.c_str(), value.c_str());
      }
    }
  }
}

void ndNetifyApiThread::CreateHeaders(
    const Headers &headers) {
  DestroyHeaders();

  string header("User-Agent: ");
  header.append(nd_get_version_and_features());
  headers_tx =
      curl_slist_append(headers_tx, header.c_str());

  headers_tx = curl_slist_append(
      headers_tx, "Content-Type: application/json");

  for (auto &h : headers) {
    header = h.first;
    header.append(": ");
    header.append(h.second);
    headers_tx =
        curl_slist_append(headers_tx, header.c_str());
  }

  curl_easy_setopt(ch, CURLOPT_HTTPHEADER, headers_tx);
}

void ndNetifyApiThread::DestroyHeaders(void) {
  if (headers_tx != nullptr) {
    curl_slist_free_all(headers_tx);
    headers_tx = nullptr;
  }
}

void ndNetifyApiThread::Perform(Method method,
                                const string &url,
                                const Headers &headers) {
  CURLcode curl_rc;

  curl_easy_setopt(ch, CURLOPT_URL, url.c_str());

  http_rc = 0;
  content.clear();
  headers_rx.clear();

  CreateHeaders(headers);

  switch (method) {
    case METHOD_GET:
      curl_easy_setopt(ch, CURLOPT_POST, 0);
      nd_dprintf("%s: %s: %s\n", tag.c_str(), "GET",
                 url.c_str());
      break;
    case METHOD_POST:
      curl_easy_setopt(ch, CURLOPT_POST, 1);
      curl_easy_setopt(ch, CURLOPT_POSTFIELDSIZE, 0);
#if 0
      curl_easy_setopt(ch, CURLOPT_POSTFIELDS,
                       payload.c_str());
#endif
      nd_dprintf("%s: %s: %s\n", tag.c_str(), "POST",
                 url.c_str());
      break;
  }

  if ((curl_rc = curl_easy_perform(ch)) != CURLE_OK)
    throw curl_rc;

  if ((curl_rc = curl_easy_getinfo(
           ch, CURLINFO_RESPONSE_CODE, &http_rc)) !=
      CURLE_OK)
    throw curl_rc;

  char *ct = nullptr;
  curl_easy_getinfo(ch, CURLINFO_CONTENT_TYPE, &ct);
  if (ct != nullptr)
    content_type = ct;
  else {
    auto i = headers_rx.find("content-type");
    if (i == headers_rx.end())
      content_type.clear();
    else {
      content_type = i->second;
    }
  }
}

void *ndNetifyApiBootstrap::Entry(void) {
  static map<ndGlobalConfig::UUID, string> uuids = {
      {ndGlobalConfig::UUID_AGENT, "X-UUID"},
      {ndGlobalConfig::UUID_SERIAL, "X-UUID-Serial"},
      {ndGlobalConfig::UUID_SITE, "X-UUID-Site"}};

  Headers headers;

  for (auto &uuid : uuids) {
    string value("-");

    if (!ndGC.LoadUUID(uuid.first, value)) {
      nd_dprintf("%s: no UUID set for: %s\n", tag.c_str(),
                 uuid.second.c_str());
    }
    headers.insert(make_pair(uuid.second, value));
  }

  string url = ndGC.url_napi;

  Perform(ndNetifyApiThread::METHOD_POST, url, headers);

  return nullptr;
}

void *ndNetifyApiDownload::Entry(void) {
  string bearer("Bearer ");
  bearer.append(token);

  Headers headers;
  headers.insert(make_pair("Authorization", bearer));

  Perform(ndNetifyApiThread::METHOD_GET, url, headers);

  return nullptr;
}

bool ndNetifyApiManager::Update(void) {
  bool result = false;

  if (token.empty()) {
    auto request = requests.find(REQUEST_BOOTSTRAP);

    if (request != requests.end()) {
      ndNetifyApiBootstrap *bootstrap =
          dynamic_cast<ndNetifyApiBootstrap *>(
              request->second);

      if (bootstrap->HasTerminated()) {
        ProcessBootstrapRequest(bootstrap);

        requests.erase(request);
        delete bootstrap;
      }
    } else {
      ndNetifyApiBootstrap *bootstrap =
          new ndNetifyApiBootstrap();
      if (bootstrap == nullptr) {
        throw ndSystemException(__PRETTY_FUNCTION__,
                                "new ndNetifyApiBootstrap",
                                ENOMEM);
      }

      auto request = requests.insert(
          make_pair(REQUEST_BOOTSTRAP, bootstrap));

      if (request.second != true)
        delete bootstrap;
      else {
        try {
          request.first->second->Create();
        } catch (ndThreadException &e) {
          nd_printf(
              "netify-api: Error creating bootstrap "
              "request: %s\n",
              e.what());
          delete bootstrap;
          requests.erase(request.first);
        }
      }
    }
  }

  if (!token.empty()) {
    nd_dprintf(
        "netify-api: TODO: check if it's time to refresh "
        "configuration.\n");
  }

  return result;
}

void ndNetifyApiManager::Terminate(void) {
  for (auto &request : requests)
    request.second->Terminate();
  for (auto &request : requests) delete request.second;
  requests.clear();
}

bool ndNetifyApiManager::ProcessBootstrapRequest(
    ndNetifyApiBootstrap *bootstrap) {
  if (bootstrap->http_rc == 0) {
    nd_printf("netify-api: Bootstrap request failed.\n");
    return false;
  }

  if (bootstrap->content.length() == 0) {
    nd_printf("netify-api: Empty bootstrap content.\n");
    return false;
  }

  if (bootstrap->content_type != "application/json") {
    nd_printf(
        "netify-api: Invalid bootstrap content "
        "type.\n");
    return false;
  }

  try {
    json content = json::parse(bootstrap->content);

    int code = -1;
    string message("Unknown");

    static vector<string> status_codes = {"status_code",
                                          "resp_code"};

    for (auto &key : status_codes) {
      auto ji = content.find(key);
      if (ji != content.end() &&
          (ji->type() == json::value_t::number_integer ||
           ji->type() == json::value_t::number_unsigned)) {
        code = ji->get<int>();
        break;
      }
    }

    static vector<string> status_messages = {
        "status_message", "resp_message"};

    for (auto &key : status_messages) {
      auto ji = content.find(key);
      if (ji != content.end() &&
          ji->type() == json::value_t::string) {
        message = ji->get<string>();
        break;
      }
    }

    if (bootstrap->http_rc != 200 || code != 0) {
      nd_printf(
          "netify-api: Bootstrap request failed: HTTP %ld: "
          "%s [%d]\n",
          bootstrap->http_rc, message.c_str(), code);
      return false;
    }

    auto jdata = content.find("data");
    if (jdata == content.end()) {
      nd_dprintf(
          "netify-api: Malformed bootstrap content: %s\n",
          "data not found");
      return false;
    }

    auto jsigs = jdata->find("signatures");
    if (jsigs == jdata->end()) {
      nd_dprintf(
          "netify-api: Malformed bootstrap content: %s\n",
          "signatures not found");
      return false;
    }

    auto jtoken = jsigs->find("token");
    if (jtoken == jsigs->end() ||
        jtoken->type() != json::value_t::string) {
      nd_dprintf(
          "netify-api: Malformed bootstrap content: %s\n",
          "token not found or invalid type");
      return false;
    }

    token = jtoken->get<string>();

    nd_dprintf("netify-api: new API token set.\n");
  } catch (exception &e) {
    nd_printf(
        "netify-api: Failed to decode bootstrap "
        "content.\n");
    nd_dprintf("netify-api: Exception: %s\n", e.what());
    return false;
  }

  return true;
}
