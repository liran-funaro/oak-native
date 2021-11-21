cmake_minimum_required(VERSION 3.20)
project(oak-native)
include_directories(inc)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-O3 -Ofast -Wall -Wextra -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
include_directories(/usr/local/include)

add_library(oak-native SHARED src/com_yahoo_oak_jni_OakNativeLib.cpp)

##############################################################################################################
# JNI
##############################################################################################################
find_package(Java 1.8 REQUIRED)
find_package(Java COMPONENTS Development)

if(APPLE)
    set(JAVA_AWT_INCLUDE_PATH " ")
    set(JAVA_INCLUDE_PATH2 " ")
endif()

find_package(JNI REQUIRED)

if(APPLE)
    list(GET JNI_INCLUDE_DIRS 0 JAVA_INCLUDE_PATH_0)
    set(JAVA_INCLUDE_PATH2 "${JAVA_INCLUDE_PATH_0}/darwin")
    find_package(JNI REQUIRED)
endif()

include_directories(${JNI_INCLUDE_DIRS})

##############################################################################################################
# folly
##############################################################################################################
set(FOLLY_INSTALL_PREFIX ../folly-build/installed)
FILE(GLOB FOLLY_INSTALLED_LIST ${FOLLY_INSTALL_PREFIX}/*)
FOREACH(subdir ${FOLLY_INSTALLED_LIST})
    include_directories(${subdir}/include)
ENDFOREACH()

find_library(FOLLY_LIBRARY NAMES folly HINTS ${FOLLY_INSTALL_PREFIX}/folly/lib)
target_link_libraries(oak-native PRIVATE ${FOLLY_LIBRARY})


##############################################################################################################
# install
##############################################################################################################
install(
        TARGETS oak-native
        LIBRARY DESTINATION lib
)
