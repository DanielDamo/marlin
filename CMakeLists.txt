cmake_minimum_required(VERSION 3.24)
project(marlin VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(include)

file(GLOB SOURCES "src/*cpp")

add_executable(marlin ${SOURCES})