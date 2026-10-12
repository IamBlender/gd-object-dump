cmake_minimum_required(VERSION 3.21)
project(ObjectDump VERSION 1.0.0)

# Tell CMake where to find the Geode SDK package installed by the workflow
if(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
endif()

find_package(Geode REQUIRED)

setup_geode_mod(ObjectDump)
