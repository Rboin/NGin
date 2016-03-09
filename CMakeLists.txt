cmake_minimum_required(VERSION 3.3)
project(snowmens)

#########################################################
# FIND GLEW                                             #
#########################################################
find_package(GLEW REQUIRED)
if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_directories(${GLEW_LIBRARY_DIRS})
endif(GLEW_FOUND)
#########################################################
# FIND GLUT                                             #
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND OPENGL                                           #
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

# on mingw not provided with cmake search
if(WIN32)
    set(GLUT_LIBRARIES libfreeglut.a)
endif(WIN32)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp engine.h steering.cpp camera.h camera.cpp render/render.h render/light.cpp render/ground.cpp render/snowmen.cpp)
add_executable(snowmens ${SOURCE_FILES})

target_link_libraries(snowmens ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})