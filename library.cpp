#include <iostream>
#include <cstring>

#include <string>
#include <unordered_map>

#include "library.h"

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

static inline uint32_t murmur_32_scramble(uint32_t k) {
    k *= 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;
    return k;
}

uint32_t murmur3_32(const uint8_t *key, size_t len, uint32_t seed) {
    uint32_t h = seed;
    uint32_t k;
    /* Read in groups of 4. */
    for (size_t i = len >> 2; i; i--) {
        // Here is a source of differing results across endiannesses.
        // A swap here has no effects on hash properties though.
        memcpy(&k, key, sizeof(uint32_t));
        key += sizeof(uint32_t);
        h ^= murmur_32_scramble(k);
        h = (h << 13) | (h >> 19);
        h = h * 5 + 0xe6546b64;
    }
    /* Read the rest. */
    k = 0;
    for (size_t i = len & 3; i; i--) {
        k <<= 8;
        k |= key[i - 1];
    }
    // A swap is *not* necessary here because the preceding loop already
    // places the low bytes in the low places according to whatever endianness
    // we use. Swaps only apply when the memory is copied in a chunk.
    h ^= murmur_32_scramble(k);
    /* Finalize. */
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
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

    long *dataLong() const {
        return (long *) asIntArray(1);
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

    Value& operator =(const Value& other) {
        release();
        address = other.address;
        return *this;
    }
};

const unsigned long noneAddress = 0;

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

long alloc(int size) {
    return Buffer::alloc(size).address;
}

void release(long bufferAddress) {
    Buffer(bufferAddress).release();
}

long build() {
    return ptrToLong(new Map());
}

void destroy(long map) {
    auto * u = longToMapPtr(map);
    for (auto & i : (*u)) {
        i.first.release();
        i.second.release();
    }
    delete u;
}

long size(long map) {
    return (long) longToMap(map).size();
}

long put(long map, long key, long value) {
    auto result = longToMap(map).insert_or_assign(Key(key), Value(value));
    if (result.second) {
        return noneAddress;
    } else {
        return result.first->second.address;
    }
}

long putIfAbsent(long map, long key, long value) {
    auto result = longToMap(map).try_emplace(Key(key), Value(value));
    if (result.second) {
        return noneAddress;
    } else {
        return result.first->second.address;
    }
}

long get(long map, long key) {
    auto u = longToMap(map);
    auto search = u.find(Key(key));
    if (search == u.end()) {
        return noneAddress;
    } else {
        return search->second.address;
    }
}

long initIterator(long map) {
    return ptrToLong(new Map::iterator(longToMap(map).begin()));
}

void destroyIterator(long iterator) {
    delete longToIteratorPtr(iterator);
}

bool hasNext(long map, long iterator) {
    return longToIterator(iterator) != longToMap(map).end();
}

void incrementIterator(long iterator) {
    ++longToIterator(iterator);
}

long getIteratorKey(long iterator) {
    return longToIterator(iterator)->first.address;
}

unsigned long getIteratorValue(long iterator) {
    return longToIterator(iterator)->second.address;
}

long nextKey(long iterator) {
    return (longToIterator(iterator)++)->first.address;
}

long nextValue(long iterator) {
    return (longToIterator(iterator)++)->second.address;
}

// Shared library interface
extern "C" {

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    alloc
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_alloc
        (JNIEnv *, jclass, jint size) {
    return alloc(size);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    release
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_yahoo_oak_cpp_DirectLib_release
(JNIEnv *, jclass, jlong address) {
    release(address);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    build
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_build
        (JNIEnv *, jclass) {
    return build();
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_yahoo_oak_cpp_DirectLib_destroy
(JNIEnv *, jclass, jlong map) {
    return destroy(map);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    size
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_size
        (JNIEnv *, jclass, jlong map) {
    return (jlong) size(map);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    put
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_put
        (JNIEnv *, jclass, jlong map, jlong key, jlong value) {
    return put(map, key, value);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    putIfAbsent
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_putIfAbsent
        (JNIEnv *, jclass, jlong map, jlong key, jlong value) {
    return putIfAbsent(map, key, value);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    get
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_get
        (JNIEnv *, jclass, jlong map, jlong key) {
    return get(map, key);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    initIterator
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_initIterator
        (JNIEnv *, jclass, jlong map) {
    return initIterator(map);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    destroyIterator
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_yahoo_oak_cpp_DirectLib_destroyIterator
(JNIEnv *, jclass, jlong map) {
    return destroyIterator(map);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    hasNext
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yahoo_oak_cpp_DirectLib_hasNext
        (JNIEnv *, jclass, jlong map, jlong iterator) {
    return hasNext(map, iterator);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    incrementIterator
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_yahoo_oak_cpp_DirectLib_incrementIterator
(JNIEnv *, jclass, jlong iterator) {
    incrementIterator(iterator);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    getIteratorKey
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_getIteratorKey
        (JNIEnv *, jclass, jlong iterator) {
    return getIteratorKey(iterator);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    getIteratorValue
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_getIteratorValue
        (JNIEnv *, jclass, jlong iterator) {
    return getIteratorValue(iterator);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    nextKey
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_nextKey
        (JNIEnv *, jclass, jlong iterator) {
    return nextKey(iterator);
}

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    nextValue
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_nextValue
        (JNIEnv *, jclass, jlong iterator) {
    return nextValue(iterator);
}

} // extern "C"
