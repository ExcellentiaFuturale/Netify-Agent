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

#include <map>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <vector>

#include "nd-flow.hpp"

using namespace std;

typedef shared_ptr<ndFlow> nd_flow_ptr;
typedef unordered_map<string, nd_flow_ptr> nd_flow_map;
typedef vector<nd_flow_map *> nd_flow_bucket;
typedef vector<unique_ptr<mutex>> nd_flow_bucket_lock;
typedef map<string, nd_flow_map *> nd_flows;
typedef pair<string, nd_flow_ptr> nd_flow_pair;
typedef pair<nd_flow_map::iterator, bool> nd_flow_insert;

class ndFlowMap
{
public:
    ndFlowMap(size_t buckets = ND_FLOW_MAP_BUCKETS);
    virtual ~ndFlowMap();

    nd_flow_ptr
    Lookup(const string &digest, bool acquire_lock = false);
    bool Insert(const string &digest, nd_flow_ptr &flow,
      bool unlocked = false);
    inline bool
    InsertUnlocked(const string &digest, nd_flow_ptr &flow) {
        return Insert(digest, flow, true);
    }

    bool Delete(const string &digest);

    nd_flow_map &Acquire(size_t b);
    const nd_flow_map &AcquireConst(size_t b) const;

    void Release(size_t b) const;
#if 0
    inline void Release(const string &digest) const {
        Release(HashToBucket(digest));
    }
#else
    void Release(const string &digest) const;
#endif
#ifndef _ND_LEAN_AND_MEAN
    void DumpBucketStats(void);
#endif

    inline size_t GetBuckets(void) const { return buckets; }

protected:
    unsigned HashToBucket(const string &digest) const {
        const char *p = digest.c_str();
        const uint64_t *b = (const uint64_t *)&p[0];
        return (*b % buckets);
    }

    size_t buckets;
    nd_flow_bucket bucket;
    mutable nd_flow_bucket_lock bucket_lock;
};
