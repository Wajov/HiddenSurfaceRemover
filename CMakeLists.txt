cmake_minimum_required(VERSION 3.17)
project(HiddenSurfaceRemover)

set(CMAKE_AUTOMOC ON)

include_directories(include)
aux_source_directory(src SOURCE)
set(HEADER
        include/ActiveEdge.h
        include/ActivePolygon.h
        include/ActiveSegment.h
        include/Edge.h
        include/ImageLabel.h
        include/Model.h
        include/NaiveHierarchicalZBuffer.h
        include/NaiveZBuffer.h
        include/Octree.h
        include/OctreeHierarchicalZBuffer.h
        include/Pixel.h
        include/Polygon.h
        include/QuadTree.h
        include/RenderWidget.h
        include/ScanlineZBuffer.h
        include/Segment.h
        include/Vertex.h
        include/ZBuffer.h
)
add_executable(HiddenSurfaceRemover
        ${HEADER}
        ${SOURCE}
)

# Assimp
find_package(assimp REQUIRED)

# glm
find_package(glm REQUIRED)

# Qt
set(QT_VERSION 5)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
target_link_libraries(
        HiddenSurfaceRemover
        assimp
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)