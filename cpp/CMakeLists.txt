cmake_minimum_required(VERSION 3.22)
project(C++)

set(CMAKE_CXX_STANDARD 20)
set(EXTENSION ".cpp")

file(GLOB FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *${EXTENSION})

foreach(file ${FILES})
    string(REPLACE ${EXTENSION} "" out ${file})
    add_executable(${out} ${file})
endforeach(file ${FILES})

subdirs("namespace")
subdirs("calculator")
subdirs("overflows")
subdirs("c")
