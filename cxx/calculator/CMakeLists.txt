cmake_minimum_required(VERSION 3.22)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt CONFIG REQUIRED)

file(GLOB files "*.cxx")
add_executable(Calculator ${files})

target_link_libraries(Calculator PRIVATE fmt::fmt)
