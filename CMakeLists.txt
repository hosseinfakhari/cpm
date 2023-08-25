# Author: hossein fakhari

cmake_minimum_required(VERSION 3.15)
project(cpm)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpm src/lib/utils.h src/main.cpp)