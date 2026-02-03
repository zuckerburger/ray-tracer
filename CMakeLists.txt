cmake_minimum_required(VERSION 3.13)
project(main)
set(SOURCE_FILES main.cpp canvas.cpp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main ${SOURCE_FILES})
