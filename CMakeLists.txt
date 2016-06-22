cmake_minimum_required(VERSION 3.0)
project(NGin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenGL REQUIRED)

# If GLM is installed, CMake doesn't have to worry about it
find_package(GLM)

find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})

set(ENGINE_SRC
        loader.cpp
        mesh.cpp
        material.cpp
        controls.cpp
        )

add_library(ngin ${ENGINE_SRC})
add_executable(preview main.cpp ${ENGINE_SRC})

target_link_libraries(preview ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})

file(COPY objects DESTINATION ./ NO_SOURCE_PERMISSIONS)
file(COPY shaders DESTINATION ./ NO_SOURCE_PERMISSIONS)
