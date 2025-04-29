cmake_minimum_required(VERSION 3.10)
project(Zadanie)
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART REQUIRED ON)

include_directories(include)

set(SOURCES 
    include/main.cpp
)

set(TEST_SOURCES
    include/main.h
    include/test.cpp
)

add_executable(stl_main ${SOURCES})
add_executable(stl_test ${TEST_SOURCES})