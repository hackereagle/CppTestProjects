cmake_minimum_required(VERSION 3.4.0)
set(PROJECT_NAME Logger)
aux_source_directory(. DIR_SRC)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(${PROJECT_NAME} SHARED ${DIR_SRC})
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} stdc++fs Threads::Threads)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_COMPILER "g++")