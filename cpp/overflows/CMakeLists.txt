cmake_minimum_required(VERSION 3.22)
project(Overflows)

set(CMAKE_CXX_STANDARD 20)
set(EXTENSION ".cpp")

file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *${EXTENSION})

foreach(file ${files})
    string(REPLACE ${EXTENSION} "" out ${file})
    add_executable(${out} ${file})
endforeach(file ${files})
