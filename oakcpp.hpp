#include <iostream>
#include <cstring>
#include <string>
#include <utility>
#include <unordered_map>

#include "murmur.h"

using namespace std;

static inline long ptrToLong(void* ptr) {
    return (long) ptr;
}

static inline uint8_t * longToBytePtr(long ptr) {
    return (uint8_t *) ptr;
}

static inline int32_t * longToIntPtr(long ptr) {
    return (int32_t *) ptr;
}


class Buffer {
    explicit Buffer(uint8_t *address) : address(ptrToLong(address)) {}

public:
    long address;

    explicit Buffer(long address) : address(address) {}

    static Buffer alloc(int size) {
        Buffer b(new uint8_t[sizeof(int) + size]);
        b.size() = size;
        return b;
    }

    void release() const {
        delete[] asByteArray();
    }

    uint8_t * asByteArray(int offset = 0) const {
        return longToBytePtr(address) + offset;
    }

    int32_t * asIntArray(int offset = 0) const {
        return longToIntPtr(address) + offset;
    }

    int &size() {
        return *asIntArray();
    }

    const int &size() const {
        return *asIntArray();
    }

    uint8_t *data() const {
        return (uint8_t *) asIntArray(1);
    }
};

class Key : public Buffer {
public:
    explicit Key(long address) : Buffer(address) {}

    bool operator==(const Key &rKey) const {
        const long size = this->size();
        if (size != rKey.size()) {
            return false;
        }
        return memcmp(this->data(), rKey.data(), size) == 0;
    }
};

namespace std {
    template<>
    class hash<Key> {
    public:
        std::size_t operator()(const Key &k) const {
            return murmur3_32(k.data(), k.size(), 0);
        }
    };
}

class Value : public Buffer {
public:
    explicit Value(long address) : Buffer(address) {}

    Value& operator =(const long) {
        return *this;
    }
};

const unsigned long NONE_ADDRESS = 0;

using Map = unordered_map<Key, Value>;


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

static inline long build() {
    return ptrToLong(new Map());
}

static inline void destroy(long map) {
    auto * u = longToMapPtr(map);
    for (auto & i : (*u)) {
        i.first.release();
        i.second.release();
    }
    delete u;
}

static inline long size(long map) {
    return (long) longToMap(map).size();
}

static inline long put(long map, long key, long value) {
    auto result = longToMap(map).insert_or_assign(Key(key), value);
    if (result.second) {
        return NONE_ADDRESS;
    } else {
        swap(result.first->second.address, value);
        return value;
    }
}

static inline long putIfAbsent(long map, long key, long value) {
    auto result = longToMap(map).try_emplace(Key(key), value);
    if (result.second) {
        return NONE_ADDRESS;
    } else {
        return result.first->second.address;
    }
}

static inline long get(long map, long key) {
    Map& u = longToMap(map);
    auto search = u.find(Key(key));
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
    return longToIterator(iterator)->first.address;
}

static inline long getIteratorValue(long iterator) {
    return longToIterator(iterator)->second.address;
}

static inline long nextKey(long iterator) {
    return (longToIterator(iterator)++)->first.address;
}

static inline long nextValue(long iterator) {
    return (longToIterator(iterator)++)->second.address;
}