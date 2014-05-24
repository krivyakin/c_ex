cmake_minimum_required(VERSION 2.6)
project(c_ex)

set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -g -O3")

set(LIB_SOURCES
	c_ex.c
	signals.c)

add_library(${CMAKE_PROJECT_NAME} STATIC ${LIB_SOURCES})

set(EXAMPLE_SOURCE
	example.c)

add_executable(example ${EXAMPLE_SOURCE})
target_link_libraries(example ${CMAKE_PROJECT_NAME})
