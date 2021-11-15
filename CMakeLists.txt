cmake_minimum_required(VERSION 3.20)
project(oakcpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux ")

add_library(liboakcpp SHARED library.cpp)
