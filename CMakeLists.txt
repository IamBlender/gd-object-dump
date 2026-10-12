cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(ObjectDump VERSION 1.0.0)

file(GLOB SOURCES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

# Pin bindings to a stable commit to avoid the CCFileUtilsWin32.h redeclaration error on main
include(CPM)
CPMAddPackage(
    NAME bindings
    GITHUB_REPOSITORY geode-sdk/bindings
    GIT_TAG v2.2081 # Or a stable commit hash if v2.2081 tag needs a specific ref
    DOWNLOAD_ONLY YES
)
set(GEODE_BINDINGS_REPO_PATH ${bindings_SOURCE_DIR})

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})
