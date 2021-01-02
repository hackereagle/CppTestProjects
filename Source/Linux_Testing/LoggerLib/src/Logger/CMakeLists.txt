cmake_minimum_required(VERSION 3.4.0)
set(PROJECT_NAME Logger)
aux_source_directory(. DIR_SRC)

add_library(${PROJECT_NAME} SHARED ${DIR_SRC})
add_executable(${PROJECT_NAME} ${DIR_SRC})
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})

set(CMAKE_VERBOSE_MAKEFILE ON)