cmake_minimum_required(VERSION 3.3)
project(parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp Field.cpp Field.h ThreadManager.cpp ThreadManager.h Exceptions.cpp Exceptions.h CommandManager.cpp CommandManager.h Worker.cpp Worker.h thread.cpp thread.h utile.cpp utile.h Manager.cpp Manager.h threadedWorker.cpp threadedWorker.h)
add_executable(parallel ${SOURCE_FILES})