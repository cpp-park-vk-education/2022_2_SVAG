cmake_minimum_required(VERSION 3.14)
project(frontend)

# variables
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# options
option(BUILD_TESTS "Build the unit tests" ON)
option(USE_SANITIZER_FLAGS "Use sanitizer flags" ON)
option(USE_COVERAGE_FLAGS "Use coverage flags" ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Boost COMPONENTS system thread REQUIRED)

set(INCS
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui
        ${CMAKE_CURRENT_SOURCE_DIR}/Workers
        ${CMAKE_CURRENT_SOURCE_DIR}/Data
        ${CMAKE_CURRENT_SOURCE_DIR}/GuiData
        ${CMAKE_CURRENT_SOURCE_DIR}/Lib
        )

set(SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/mainwindow.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/mainwindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/mainwindow.cpp
        )

# setup
if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG")
    #    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Werror")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g0 -DNDEBUG")
    set(USE_SANITIZER_FLAGS OFF)
    set(USE_COVERAGE_FLAGS OFF)
endif ()

if (USE_SANITIZER_FLAGS)
    #    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
endif ()

add_executable(${CMAKE_PROJECT_NAME} ${SRCS})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${INCS})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        Qt5::Core Qt5::Gui Qt5::Widgets
        ${Boost_LIBRARIES}
        )

# tests
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(Test)
endif ()
