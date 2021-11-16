cmake_minimum_required(VERSION 3.20)
project(oakcpp)

find_package(Java 1.8 REQUIRED)
find_package(Java COMPONENTS Development)

find_package(JNI)
INCLUDE_DIRECTORIES(${JNI_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

add_library(oakcpp SHARED library.cpp)

install(
        TARGETS oakcpp
        LIBRARY DESTINATION lib
)
