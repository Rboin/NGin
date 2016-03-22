cmake_minimum_required(VERSION 3.3)
project(game_engine)

find_package(OPENGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})

if(WIN32)
    set(GLUT_LIBRARIES libfreeglut.a)
    set(GLEW_LIBRARIES libglew32.a libglew32.dll.a)
endif(WIN32)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp engine.h loader.h loader.cpp mesh.h mesh.cpp material.h material.cpp controls.h controls.cpp default_values.h)
add_executable(game_engine ${SOURCE_FILES})

target_link_libraries(game_engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})

file(COPY objects DESTINATION / NO_SOURCE_PERMISSIONS)
file(COPY shaders DESTINATION / NO_SOURCE_PERMISSIONS)
