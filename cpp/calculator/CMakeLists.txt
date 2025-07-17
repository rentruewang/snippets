cmake_minimum_required(VERSION 3.22)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)

file(GLOB FILES "*.cpp")
add_executable(Calculator ${FILES})
