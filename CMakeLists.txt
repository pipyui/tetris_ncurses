# Declare the project.
# CXX means that the project is written in C++.
project(tetris CXX)

# We require CMake-2.8 in order to build the program.
cmake_minimum_required(VERSION 2.8)

# Enable compilation with C++11
# Turn on all warnings and make them errors.
set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11 -lncurses")

# Add an executable program to be built from the
# given source code files.
add_executable(tetris main.cpp tetris.cpp ncurses_wrapper.cpp)
