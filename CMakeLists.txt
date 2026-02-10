cmake_minimum_required(VERSION 3.13)
project(RayTracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather source files
file(GLOB LIB_SOURCES src/*.cpp)

# Create the library
add_library(RayTracerLib ${LIB_SOURCES})

# Include directories
target_include_directories(RayTracerLib
  PUBLIC include
  PRIVATE src
)

# Build example executable
add_executable(main)
target_sources(main
  PRIVATE
  examples/main.cpp
)
target_link_libraries(main PRIVATE RayTracerLib)

