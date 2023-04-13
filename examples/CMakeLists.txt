cmake_minimum_required(VERSION 3.3.2)
project(libev_wrapper_examples VERSION 0.9.0 DESCRIPTION "examples for libev_wrapper")

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp )

target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads libev_wrapper)
