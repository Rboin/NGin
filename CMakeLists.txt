cmake_minimum_required(VERSION 3.3)
project(gp_3)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(gp_3 ${SOURCE_FILES})

target_link_libraries(gp_3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )