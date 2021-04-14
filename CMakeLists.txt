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

OPTION (USE_OPENMP "Use OpenMP to enamble <omp.h>" ON)

macro(append var value)
    set(${var} "${${var}} ${value}")
endmacro()

if(USE_OPENMP)
    if (APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(_omp_severity "WARNING")
    else()
        set(_omp_severity "FATAL_ERROR")
    endif()
    find_package(OpenMP)
    if(OpenMP_CXX_FOUND)
        append(CMAKE_C_FLAGS ${OpenMP_C_FLAGS})
        append(CMAKE_CXX_FLAGS ${OpenMP_CXX_FLAGS})
        add_definitions(-DXIUXIAN_WITH_OPENMP)
        if(MSVC AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            list(APPEND EXTRA_SHARED_LIBS ${OpenMP_CXX_LIBRARIES})
        endif()
    else()
        message(${_omp_severity} "OpenMP library could not be found. "
            "Proceeding might lead to highly sub-optimal performance.")
    endif()
endif()

enable_testing()

add_subdirectory(graph)
add_subdirectory(sort)
add_subdirectory(thread)
