# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MyProject VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(test)

# Add directories for includes
include_directories(src)

# Add the main executable
add_executable(MyProjectMain main.cpp)

# Link the main executable with the project library
target_link_libraries(MyProjectMain PRIVATE MyProjectLib)
