cmake_minimum_required(VERSION 3.4.0)
set(PROJECT_NAME TestState)
project(${PROJECT_NAME})
aux_source_directory(. DIR_SRC)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} ${DIR_SRC})
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} stdc++fs)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)