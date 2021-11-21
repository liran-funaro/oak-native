#include <jni.h>
#include <jni_md.h>

#include "oakfolly.hpp"
#include "com_yahoo_oak_jni_OakNativeLib.h"

// Shared library interface
extern "C" {

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_alloc
        (JNIEnv *, jclass, jint size) {
    return Buffer::alloc(size).address;
}

JNIEXPORT void JNICALL Java_com_yahoo_oak_jni_OakNativeLib_release
        (JNIEnv *, jclass, jlong address) {
    Buffer(address).release();
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_build
        (JNIEnv *, jclass, jlong maxPopulation) {
    FollyMap::Config c;
    c.maxLoadFactor = 0.5;
    return ptrToLong(new Map(maxPopulation, c));
}

JNIEXPORT void JNICALL Java_com_yahoo_oak_jni_OakNativeLib_destroy
        (JNIEnv *, jclass, jlong map) {
    auto * u = longToMapPtr(map);
    for (auto & i : (*u).m) {
        Buffer(i.first).release();
        i.second.release();
    }
    delete u;
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_size
        (JNIEnv *, jclass, jlong map) {
    return (long) longToMap(map).m.size();
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_allocatedBytes
        (JNIEnv *, jclass, jlong map) {
    return (long) longToMap(map).allocatedBytes.load();
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_countedAlloc
        (JNIEnv *, jclass, jlong map, jint size) {
    return countedAlloc(map, size);
}

JNIEXPORT void JNICALL Java_com_yahoo_oak_jni_OakNativeLib_countedRelease
        (JNIEnv *, jclass, jlong map, jlong address) {
    countedRelease(map, address);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_put
        (JNIEnv *, jclass, jlong map, jlong key, jlong value) {
    auto result = longToMap(map).m.emplace(key, Value(value));
    if (result.second) {
        return NONE_ADDRESS;
    } else {
        return result.first->second.exchange(value);
    }
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_putIfAbsent
        (JNIEnv *, jclass, jlong map, jlong key, jlong value) {
    auto result = longToMap(map).m.emplace(key, Value(value));
    if (result.second) {
        return NONE_ADDRESS;
    } else {
        return result.first->second.address;
    }
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_get
        (JNIEnv *, jclass, jlong map, jlong key) {
    auto& u = longToMap(map);
    auto search = u.m.find(key);
    if (search == u.m.end()) {
        return NONE_ADDRESS;
    } else {
        return search->second.address;
    }
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_remove
        (JNIEnv *, jclass, jlong map, jlong key) {
    auto& u = longToMap(map);
    auto search = u.m.find(key);
    if (search == u.m.end()) {
        return NONE_ADDRESS;
    } else {
        long value = search->second.exchange(NONE_ADDRESS);
        if (value == NONE_ADDRESS) {
            return NONE_ADDRESS;
        }
        countedRelease(map, search->first);
        return value;
    }
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorInit
        (JNIEnv *, jclass, jlong map) {
    return ptrToLong(new FollyMap::iterator(longToMap(map).m.begin()));
}

JNIEXPORT void JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorDestroy
        (JNIEnv *, jclass, jlong map) {
    delete longToIteratorPtr(map);
}

JNIEXPORT jboolean JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorHasNext
        (JNIEnv *, jclass, jlong map, jlong iterator) {
    return longToIterator(iterator) != longToMap(map).m.end();
}

JNIEXPORT void JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorIncrement
        (JNIEnv *, jclass, jlong iterator) {
    ++longToIterator(iterator);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorGetKey
        (JNIEnv *, jclass, jlong iterator) {
    return longToIterator(iterator)->first;
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorGetValue
        (JNIEnv *, jclass, jlong iterator) {
    return longToIterator(iterator)->second.address;
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorNextKey
        (JNIEnv *, jclass, jlong iterator) {
    return (longToIterator(iterator)++)->first;
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorNextValue
        (JNIEnv *, jclass, jlong iterator) {
    return (longToIterator(iterator)++)->second.address;
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorRemove
        (JNIEnv *, jclass, jlong) {
    return NONE_ADDRESS;
}

} // extern "C"
