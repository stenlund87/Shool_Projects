cmake_minimum_required(VERSION 3.8)
project(Assignment_1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(SOURCE_FILES main.cpp)
add_executable(Assignment_1 ${SOURCE_FILES})