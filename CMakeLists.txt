# CMakeLists.txt
# Mark Guerra
# 11/1/2015

cmake_minimum_required(VERSION 2.6)
project(BigNumber)

set(BigNumber_VERSION_MAJOR 1)
set(BigNumber_VERSION_MINOR 0)

set(c++version -std=c++11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic -Wno-unused-function ${c++version}")

set(SOURCE_FILES
        src/bignumber.cpp  main.cpp )

add_library(BigNumber ${SOURCE_FILES})

if(WIN32)
    install(TARGETS BigNumber DESTINATION C:/Libs/BigNumber/lib)
    install(FILES src/bignumber.h DESTINATION C:/Libs/BigNumber/include)
else()
    install(TARGETS BigNumber DESTINATION ~/Library/Frameworks/BigNumber/lib)
    install(FILES src/bignumber.h DESTINATION ~/Library/Frameworks/BigNumber/include)
endif()

add_custom_command(
        TARGET BigNumber
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install
)

add_executable(BigNumberRun ${SOURCE_FILES})
