# CMakeLists.txt
# Mark Guerra
# 11/1/2015

cmake_minimum_required(VERSION 3.3)
project(BigNumber)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/bignumber.cpp  main.cpp )

add_executable(BigNumber ${SOURCE_FILES})