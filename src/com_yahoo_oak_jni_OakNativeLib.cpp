#include <jni.h>
#include <jni_md.h>

#include "oakfolly.hpp"
#include "com_yahoo_oak_jni_OakNativeLib.h"

// Shared library interface
extern "C" {

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_alloc
        (JNIEnv *, jclass, jint size) {
    return alloc(size);
}

JNIEXPORT jint JNICALL Java_com_yahoo_oak_jni_OakNativeLib_release
        (JNIEnv *, jclass, jlong address) {
    return release(address);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_build
        (JNIEnv *, jclass, jlong maxPopulation) {
    return build(maxPopulation);
}

JNIEXPORT void JNICALL Java_com_yahoo_oak_jni_OakNativeLib_destroy
        (JNIEnv *, jclass, jlong map) {
    return destroy(map);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_size
        (JNIEnv *, jclass, jlong map) {
    return (jlong) size(map);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_put
        (JNIEnv *, jclass, jlong map, jlong key, jlong value) {
    return put(map, key, value);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_putIfAbsent
        (JNIEnv *, jclass, jlong map, jlong key, jlong value) {
    return putIfAbsent(map, key, value);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_get
        (JNIEnv *, jclass, jlong map, jlong key) {
    return get(map, key);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_remove
        (JNIEnv *, jclass, jlong map, jlong key) {
    return NONE_ADDRESS;
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorInit
        (JNIEnv *, jclass, jlong map) {
    return initIterator(map);
}

JNIEXPORT void JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorDestroy
        (JNIEnv *, jclass, jlong map) {
    return destroyIterator(map);
}

JNIEXPORT jboolean JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorHasNext
        (JNIEnv *, jclass, jlong map, jlong iterator) {
    return hasNext(map, iterator);
}

JNIEXPORT void JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorIncrement
        (JNIEnv *, jclass, jlong iterator) {
    incrementIterator(iterator);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorGetKey
        (JNIEnv *, jclass, jlong iterator) {
    return getIteratorKey(iterator);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorGetValue
        (JNIEnv *, jclass, jlong iterator) {
    return getIteratorValue(iterator);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorNextKey
        (JNIEnv *, jclass, jlong iterator) {
    return nextKey(iterator);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorNextValue
        (JNIEnv *, jclass, jlong iterator) {
    return nextValue(iterator);
}

JNIEXPORT jlong JNICALL Java_com_yahoo_oak_jni_OakNativeLib_iteratorRemove
        (JNIEnv *, jclass, jlong iterator) {
    return NONE_ADDRESS;
}

} // extern "C"
