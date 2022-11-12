cmake_minimum_required(VERSION 3.0.0)
project(database)

if (TEST_MODE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
endif()

add_library(${PROJECT_NAME} database.cpp)

set(DATABASE_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(DATABASE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
