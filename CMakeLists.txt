cmake_minimum_required(VERSION 3.20)
project(Bus_System)

set(CMAKE_CXX_STANDARD 14)

include_directories(Classes)

add_executable(Bus_System
        Classes/main.cpp
        Classes/main.h)
