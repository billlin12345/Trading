project(AlgoTradingTest)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

add_subdirectory(cointegration)
add_subdirectory(include)
add_subdirectory(src)

file(GLOB HEADERS "include/*.hpp")
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADERS} ${SOURCES})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
