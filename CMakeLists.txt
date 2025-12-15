# MARLIN

cmake_minimum_required(VERSION 3.24)
project(marlin VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Packages
find_package(Curses REQUIRED)
find_package(nlohmann_json REQUIRED)


file(GLOB_RECURSE SOURCES "src/*cpp")

add_executable(marlin ${SOURCES})

# LINKING
target_include_directories(marlin PRIVATE include)
target_link_libraries(marlin PRIVATE ${CURSES_LIBRARIES})
target_include_directories(marlin PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(marlin PRIVATE nlohmann_json::nlohmann_json)
