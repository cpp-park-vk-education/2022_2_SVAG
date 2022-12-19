cmake_minimum_required(VERSION 3.14)
project(unit_test)

# variables
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (USE_SANITIZER_FLAGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
endif ()

if (USE_COVERAGE_FLAGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif ()

find_package(GTest REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(${PROJECT_NAME}
        test_frontend.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Ui/mainwindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Ui/board.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Ui/column.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Ui/card.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Ui/comment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Ui/update.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Ui/user.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Ui/menu.cpp
        )
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../
        ${CMAKE_CURRENT_SOURCE_DIR}/../Managers
        ${CMAKE_CURRENT_SOURCE_DIR}/../Ui
        )
target_link_libraries(${PROJECT_NAME} GTest::gtest_main
        Qt5::Core Qt5::Gui Qt5::Widgets
        )

gtest_discover_tests(${PROJECT_NAME})
