cmake_minimum_required(VERSION 3.14.0)

find_package(libev QUIET)

if (libev_FOUND)
    return()
endif()

message(STATUS "couldn't find libev in system. will download it")

include(FetchContent)
FetchContent_Declare(
  libev
  GIT_REPOSITORY https://github.com/vdm4k/libev-cmake
)

FetchContent_MakeAvailable(libev)
