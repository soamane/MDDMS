cmake_minimum_required(VERSION 3.14)

project(MyProject)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Sql)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.hpp)

add_executable(MyProject main.cpp ${SRC_FILES})

target_link_libraries(MyProject Qt5::Core Qt5::Sql Qt5::Widgets)
