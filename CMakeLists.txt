cmake_minimum_required(VERSION 2.9)
message(STATUS "cmake version: ${CMAKE_VERSION}")

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    message(STATUS "CMAKE_BUILD_TYPE is unset, defaulting to Release")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel RelWithAssert ...")
endif()

# xiuxian

set(LIB_NAME xiuxian)
set(PROJECT_NAME "xiuxian")
set(PROJECT_FULL_NAME "play with algorithm")
set(PROJECT_VERSION 0.1.0)

if (CMAKE_VERSION VERSION_LESS 3.0)
    project(${PROJECT_NAME} C CXX)
else()
    cmake_policy(SET CMP0048 NEW)
    project(${PROJECT_NAME} VERSION "${PROJECT_VERSION}" LANGUAGES C CXX)
endif()

string(REPLACE "." ";" VERSION_LIST ${PROJECT_VERSION})
list(GET VERSION_LIST 0 DNNL_GRAPH_VERSION_MAJOR)
list(GET VERSION_LIST 1 DNNL_GRAPH_VERSION_MINOR)
list(GET VERSION_LIST 2 DNNL_GRAPH_VERSION_PATCH)

if(UNIX OR MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

add_subdirectory(sort)
