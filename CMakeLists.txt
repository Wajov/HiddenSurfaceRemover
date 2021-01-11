cmake_minimum_required(VERSION 3.17)
project(HiddenSurfaceRemover)

include_directories(include)
aux_source_directory(src SOURCE)
add_executable(HiddenSurfaceRemover ${SOURCE} src/Polygon.cpp include/Polygon.h)

# Assimp
find_package(assimp REQUIRED)

# Qt
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
target_link_libraries(
        HiddenSurfaceRemover
        assimp
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)