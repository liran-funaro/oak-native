#include <ios>
#include <iostream>
#include <cstring>
#include <string>
#include <utility>
#include <unordered_map>
#include <atomic>

#include "murmur.h"

#ifndef _key_value_hpp
#define _key_value_hpp

#include <jni.h>

const unsigned long NONE_ADDRESS = 0;

using namespace std;

static inline long ptrToLong(void* ptr) {
    return (long) ptr;
}

static inline uint8_t * longToBytePtr(long ptr) {
    return (uint8_t *) ptr;
}


class Buffer {
    explicit Buffer(uint8_t *address) : address(ptrToLong(address)) {}

public:
    long address;

    explicit Buffer(long address) : address(address) {}

    static Buffer alloc(int size) {
        Buffer b(new uint8_t[sizeof(jint) + size]);
        b.size() = size;
        return b;
    }

    void release() const {
        delete[] asByteArray();
    }

    [[nodiscard]] uint8_t * asByteArray() const {
        return ((uint8_t *) address);
    }

    [[nodiscard]] jint * asIntArray() const {
        return ((jint *) address);
    }

    [[nodiscard]] jint & size() const {
        return *asIntArray();
    }

    [[nodiscard]] uint8_t *data() const {
        return (uint8_t *) (asIntArray() + 1);
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

static inline uint32_t keyHash(const Key &k) {
    return murmur3_32(k.data(), k.size(), 0);
}

namespace std {
    template<>
    class hash<Key> {
    public:
        std::size_t operator()(const Key &k) const {
            return keyHash(k);
        }
    };

    template<>
    class equal_to<Key> {
    public:
        bool operator()(const Key &lhs, const Key &rhs) const {
            return lhs == rhs;
        }
    };
}

class Value {
public:
    atomic<long> address;
    explicit Value(long address) : address(address) {}
    explicit Value(const Value& val) : address(val.address.load()) {}

    long exchange(long value) {
        return address.exchange(value);
    }

    jint release() {
        long toRelease = address.exchange(NONE_ADDRESS);
        if (toRelease == NONE_ADDRESS) {
            return false;
        }

        jint size = *((jint *) toRelease);
        delete[] longToBytePtr(toRelease);
        return size;
    }

    Value& operator =(const long) {
        // We don't assign the address here because we don't want "lose" the old address.
        // We swap the addresses later and return the old address to the user.
        return *this;
    }
};

#endif