cmake_minimum_required(VERSION 3.0)
#version requirement

project(demo)
#project name

enable_testing()

set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
#set the directory of generated document to "/buid"

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
#subdirectory of source code: "/src"

add_subdirectory(${PROJECT_SOURCE_DIR}/tst)
