cmake_minimum_required(VERSION 3.21)
include($ENV{GEODE_SDK}/cmake/Geode.cmake)
project(object-dump)

setup_geode_mod(ObjectDump)

if(MSVC)
    add_compile_options(/wd4005 /wd4099)
else()
    add_compile_options(-Wno-error=class-memaccess -Wno-error=duplicate-enum -Wno-error=inconsistent-missing-override)
endif()
