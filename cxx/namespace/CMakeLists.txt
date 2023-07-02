cmake_minimum_required(VERSION 3.10)
project(Namespaces)

set(CMAKE_CXX_STANDARD 20)
set(EXTENSION ".cxx")

file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *${EXTENSION})

foreach(file ${files})
    string(REPLACE ${EXTENSION} "" out ${file})
    add_executable(${out} ${file})
endforeach(file ${files})
