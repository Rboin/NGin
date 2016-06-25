cmake_minimum_required(VERSION 3.0)
project(NGin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lfreeimage")

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
        src/mesh.cpp
        src/material.cpp
        src/controls.cpp
        src/shader.cpp src/object3d.cpp)

add_library(ngin ${ENGINE_SRC})
add_executable(preview src/preview.cpp ${ENGINE_SRC})

target_link_libraries(preview ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})

file(COPY objects DESTINATION bin NO_SOURCE_PERMISSIONS)
file(COPY shaders DESTINATION bin NO_SOURCE_PERMISSIONS)
