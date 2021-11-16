cmake_minimum_required(VERSION 3.20)
project(oakcpp)

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

INCLUDE_DIRECTORIES(${JNI_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-O3 -Ofast -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_library(oakcpp SHARED com_yahoo_oak_cpp_DirectLib.cpp)

install(
        TARGETS oakcpp
        LIBRARY DESTINATION lib
)
