/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_yahoo_oak_cpp_DirectLib */

#ifndef _Included_com_yahoo_oak_cpp_DirectLib
#define _Included_com_yahoo_oak_cpp_DirectLib
#ifdef __cplusplus
extern "C" {
#endif
#undef com_yahoo_oak_cpp_DirectLib_NONE_ADDRESS
#define com_yahoo_oak_cpp_DirectLib_NONE_ADDRESS 0LL
/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    alloc
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_alloc
        (JNIEnv *, jclass, jint);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    release
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_yahoo_oak_cpp_DirectLib_release
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    build
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_build
        (JNIEnv *, jclass);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_yahoo_oak_cpp_DirectLib_destroy
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    size
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_size
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    put
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_put
        (JNIEnv *, jclass, jlong, jlong, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    putIfAbsent
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_putIfAbsent
        (JNIEnv *, jclass, jlong, jlong, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    get
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_get
        (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    initIterator
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_initIterator
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    destroyIterator
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_yahoo_oak_cpp_DirectLib_destroyIterator
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    hasNext
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yahoo_oak_cpp_DirectLib_hasNext
        (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    incrementIterator
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_yahoo_oak_cpp_DirectLib_incrementIterator
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    getIteratorKey
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_getIteratorKey
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    getIteratorValue
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_getIteratorValue
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    nextKey
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_nextKey
        (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yahoo_oak_cpp_DirectLib
 * Method:    nextValue
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_yahoo_oak_cpp_DirectLib_nextValue
        (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif