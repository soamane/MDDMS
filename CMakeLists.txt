cmake_minimum_required(VERSION 3.14)

project(MyProject)

# Поиск Qt5 и библиотек Core и SQL
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Sql)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

# Добавление всех .cpp и .hpp файлов из папки src/ и ее подпапок
file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.hpp)

# Список исходных файлов вашего проекта
add_executable(MyProject main.cpp ${SRC_FILES})

# Линкуем с Qt5
target_link_libraries(MyProject Qt5::Core Qt5::Sql Qt5::Widgets)
