cmake_minimum_required(VERSION 3.14.0)
project(libev_wrapper VERSION 0.9.0 DESCRIPTION "network library")

set(H_FILES
    include/libev_wrapper/classic_api.h
    include/libev_wrapper/factory.h
    include/libev_wrapper/event.h
    include/libev_wrapper/base_event.h
    include/libev_wrapper/timer.h
)

set(CPP_FILES
    source/libev_wrapper/classic_api.cpp
    source/libev_wrapper/factory.cpp
    source/libev_wrapper/event.cpp
    source/libev_wrapper/base_event.cpp
    source/libev_wrapper/timer.cpp
)

include("${PROJECT_SOURCE_DIR}/third_party/libev.cmake")

add_library(${PROJECT_NAME} ${CPP_FILES} ${H_FILES})
add_library(bro::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE  -Wall -Wextra -Wpedantic -Wno-vla -Wno-unused-local-typedefs)

# TODO: maybe we need to add only not secure (without SSL)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

#sanitizer
option(WITH_SANITIZER "Enable address sanitizer" OFF)

if(WITH_SANITIZER)
    target_compile_options(${PROJECT_NAME} INTERFACE -fsanitize=address -fPIC)
    target_link_options(${PROJECT_NAME} INTERFACE -fsanitize=address)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ev::ev)

#examples
option(WITH_EXAMPLES "Build examples" OFF)
if(WITH_EXAMPLES)
    add_subdirectory(examples)
endif()
