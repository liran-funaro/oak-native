#include <iostream>
#include <cstring>
#include <string>
#include <utility>
#include <atomic>

#include <folly/AtomicHashMap.h>

#include "keyvalue.hpp"

#ifndef _oak_junction_hpp
#define _oak_junction_hpp


class hash_long {
public:
    std::size_t operator()(const long k) const {
        return keyHash(Key(k));
    }
};

static inline bool isValidKey(long address) {
    return address > 0;
}

class equal_to_long {
public:
    bool operator()(const long lhs, const long rhs) const {
        if (!isValidKey(lhs) || !isValidKey(rhs)) {
            return false;
        }
        return Key(lhs) == Key(rhs);
    }
};

using FollyMap = folly::AtomicHashMap<long, Value, hash_long, equal_to_long>;

class Map {
public:
    folly::AtomicHashMap<long, Value, hash_long, equal_to_long> m;
    atomic<unsigned long> allocatedBytes;

    Map(long maxPopulation, const FollyMap::Config& c) : m(maxPopulation, c), allocatedBytes(0) {}
};


static inline Map * longToMapPtr(long ptr) {
    return (Map *) ptr;
}

static inline Map& longToMap(long ptr) {
    return *longToMapPtr(ptr);
}

static inline FollyMap::iterator * longToIteratorPtr(long ptr) {
    return (FollyMap::iterator *) ptr;
}

static inline FollyMap::iterator & longToIterator(long ptr) {
    return *longToIteratorPtr(ptr);
}

static inline long countedAlloc(long map, int size) {
    auto& u = longToMap(map);
    long ret = Buffer::alloc(size).address;
    u.allocatedBytes.fetch_add((unsigned long) size + sizeof(jint));
    return ret;
}

static inline void countedRelease(long map, long bufferAddress) {
    Buffer b(bufferAddress);
    int size = b.size();
    b.release();
    longToMap(map).allocatedBytes.fetch_sub((unsigned long) size + sizeof(jint));
}

#endif
