cmake_minimum_required(VERSION 3.23)
project(AERSP424_HW1)
set(CMAKE_CXX_STANDARD 20)
include_directories(${CMAKE_SOURCE_DIR})
add_executable(${AERSP424_HW1} main_hw1.cpp functions_hw1.h functions_hw1.cpp)