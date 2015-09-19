cmake_minimum_required(VERSION 3.3)
project(parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Field.cpp Field.h ThreadManager.cpp ThreadManager.h Exeptions.cpp Exeptions.h CommandManager.cpp CommandManager.h)
add_executable(parallel ${SOURCE_FILES})