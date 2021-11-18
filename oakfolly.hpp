#include <iostream>
#include <cstring>
#include <string>
#include <utility>

#include <folly/AtomicHashMap.h>

#include "keyvalue.hpp"

#ifndef _oak_junction_hpp
#define _oak_junction_hpp


const unsigned long NONE_ADDRESS = 0;

class hash_long {
public:
    std::size_t operator()(const long k) const {
        return keyHash(Key(k));
    }
};

class equal_to_long {
public:
    bool operator()(const long lhs, const long rhs) const {
        return Key(lhs) == Key(rhs);
    }
};

using Map = folly::AtomicHashMap<long, Value, hash_long, equal_to_long>;


static inline Map * longToMapPtr(long ptr) {
    return (Map *) ptr;
}

static inline Map& longToMap(long ptr) {
    return *longToMapPtr(ptr);
}

static inline Map::iterator * longToIteratorPtr(long ptr) {
    return (Map::iterator *) ptr;
}

static inline Map::iterator & longToIterator(long ptr) {
    return *longToIteratorPtr(ptr);
}


static inline long alloc(int size) {
    return Buffer::alloc(size).address;
}

static inline int release(long bufferAddress) {
    Buffer b(bufferAddress);
    int sz = b.size();
    b.release();
    return sz;
}

static inline long build(long maxPopulation) {
    return ptrToLong(new Map(maxPopulation));
}

static inline void destroy(long map) {
    auto * u = longToMapPtr(map);
    for (auto & i : (*u)) {
        Key(i.first).release();
        i.second.release();
    }
    delete u;
}

static inline long size(long map) {
    return (long) longToMap(map).size();
}

static inline long put(long map, long key, long value) {
    auto result = longToMap(map).emplace(key, value);
    if (result.second) {
        return NONE_ADDRESS;
    } else {
        swap(result.first->second.address, value);
        return value;
    }
}

static inline long putIfAbsent(long map, long key, long value) {
    auto result = longToMap(map).emplace(key, value);
    if (result.second) {
        return NONE_ADDRESS;
    } else {
        return result.first->second.address;
    }
}

static inline long get(long map, long key) {
    Map& u = longToMap(map);
    auto search = u.find(key);
    if (search == u.end()) {
        return NONE_ADDRESS;
    } else {
        return search->second.address;
    }
}

static inline long initIterator(long map) {
    return ptrToLong(new Map::iterator(longToMap(map).begin()));
}

static inline void destroyIterator(long iterator) {
    delete longToIteratorPtr(iterator);
}

static inline bool hasNext(long map, long iterator) {
    return longToIterator(iterator) != longToMap(map).end();
}

static inline void incrementIterator(long iterator) {
    ++longToIterator(iterator);
}

static inline long getIteratorKey(long iterator) {
    return longToIterator(iterator)->first;
}

static inline long getIteratorValue(long iterator) {
    return longToIterator(iterator)->second.address;
}

static inline long nextKey(long iterator) {
    return (longToIterator(iterator)++)->first;
}

static inline long nextValue(long iterator) {
    return (longToIterator(iterator)++)->second.address;
}

#endif
