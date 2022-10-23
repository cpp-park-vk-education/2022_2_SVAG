cmake_minimum_required(VERSION 3.14)
project(DoIt)

OPTION(TEST "Run test" OFF)
add_subdirectory(database)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCES})

if (TEST_MODE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${DATABASE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${DATABASE_LIBRARIES})

# tests
enable_testing()
add_subdirectory(tests)