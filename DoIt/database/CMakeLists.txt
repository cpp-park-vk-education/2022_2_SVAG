cmake_minimum_required(VERSION 3.0.0)
project(database)

if (TEST_MODE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
endif()


file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})

set(DATABASE_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(DATABASE_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)