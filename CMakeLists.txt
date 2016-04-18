# CMakeLists.txt
# Mark Guerra
# 11/1/2015

cmake_minimum_required(VERSION 3.3)
project(BigNumber)

set(BigNumber_VERSION_MAJOR 1)
set(BigNumber_VERSION_MINOR 0)

set(c++version -std=c++11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic ${c++version}")

set(SOURCE_FILES
        src/bignumber.cpp  main.cpp )

add_executable(BigNumber ${SOURCE_FILES})