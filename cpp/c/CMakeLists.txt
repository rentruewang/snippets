cmake_minimum_required(VERSION 3.10)
project(C)

set(CMAKE_C_STANDARD 17)
set(EXTENSION ".c")

file(GLOB FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *${EXTENSION})

foreach(file ${FILES})
    string(REPLACE ${EXTENSION} "" out ${file})
    add_executable(${out} ${file})
endforeach(file ${FILES})
