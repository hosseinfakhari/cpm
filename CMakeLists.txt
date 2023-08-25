# Author: hossein fakhari

cmake_minimum_required(VERSION 3.15)
project(cpm)

set(CMAKE_CXX_STANDARD 20)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(cpm src/lib/utils.h src/main.cpp)
target_link_libraries(cpm PRIVATE nlohmann_json::nlohmann_json)