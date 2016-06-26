cmake_minimum_required(VERSION 3.0)
project(NGin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# export with UNIX dir structure
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})

set(ENGINE_SRC
        src/shader.cpp
        src/controls.cpp
        src/mesh.cpp
        src/material.cpp
        src/object3d.cpp src/window.cpp)

include_directories(include)

add_library(ngin ${ENGINE_SRC})
add_executable(preview src/preview.cpp ${ENGINE_SRC})

target_link_libraries(ngin  ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
target_link_libraries(preview  ngin)

file(COPY local/ DESTINATION local)
