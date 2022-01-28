cmake_minimum_required(VERSION 3.20)
project(Bus_System)

set(CMAKE_CXX_STANDARD 14)

include_directories(Classes)

add_executable(Bus_System main.cpp
        Classes/minHeap.h
        Classes/minHeap.cpp
        Classes/graph.h
        Classes/graph.cpp
        Classes/App.h
        Classes/App.cpp
        Classes/FileReader.cpp
        Classes/FileReader.h Classes/LinesGraph.cpp Classes/LinesGraph.h)
