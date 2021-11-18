cmake_minimum_required(VERSION 3.20)
project(oakcpp)

##############################################################################################################
# other
##############################################################################################################
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-O3 -Ofast -Wall -Wextra -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_library(oakcpp SHARED com_yahoo_oak_cpp_DirectLib.cpp)

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
link_directories(folly/lib)
include_directories(folly/include)
target_link_libraries(oakcpp PRIVATE folly)


##############################################################################################################
# install
##############################################################################################################
install(
        TARGETS oakcpp
        LIBRARY DESTINATION lib
)
