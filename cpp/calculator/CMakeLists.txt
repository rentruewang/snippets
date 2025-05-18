cmake_minimum_required(VERSION 3.22)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt CONFIG REQUIRED)

file(GLOB FILES "*.cpp")
add_executable(Calculator ${FILES})

target_link_libraries(Calculator PRIVATE fmt::fmt)
