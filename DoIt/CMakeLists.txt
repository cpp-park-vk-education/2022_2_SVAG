cmake_minimum_required(VERSION 3.14)
project(DoIt)

OPTION(TEST "Run test" OFF)
add_subdirectory(database)
add_subdirectory(frontend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} main.cpp)

if (TEST_MODE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif()

if (MEM_MODE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=leak -fsanitize=undefined -g -OX")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${DATABASE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${DATABASE_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${FRONTEND_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FRONTEND_LIBRARIES})

# tests
enable_testing()
add_subdirectory(tests)
