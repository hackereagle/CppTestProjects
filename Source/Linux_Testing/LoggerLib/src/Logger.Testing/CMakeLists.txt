cmake_minimum_required(VERSION 3.4.0)
set(PROJECT_NAME LoggerTesting)
aux_source_directory(. DIR_SRC)
set(CMAKE_CXX_STANDARD 17)

add_library(myLib SHARED IMPORTED)
# message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
set_target_properties(myLib PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/src/Logger/libLogger.so)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${DIR_SRC})
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} myLib Threads::Threads)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_COMPILER "g++")