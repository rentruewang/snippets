cmake_minimum_required(VERSION 3.10)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)

file(GLOB files "*.cxx")
add_executable(Calculator ${files})
