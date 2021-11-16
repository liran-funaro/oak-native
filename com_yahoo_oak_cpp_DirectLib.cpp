#include <jni.h>
#include <jni_md.h>

#include "oakcpp.hpp"
#include "com_yahoo_oak_cpp_DirectLib.h"

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
JNIEXPORT jint JNICALL Java_com_yahoo_oak_cpp_DirectLib_release
        (JNIEnv *, jclass, jlong address) {
    return release(address);
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
