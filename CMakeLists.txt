cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(ATM)

add_executable(
    main
    src/driver.cpp
)