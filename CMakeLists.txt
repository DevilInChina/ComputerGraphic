cmake_minimum_required(VERSION 3.17)
project(CG)

set(CMAKE_CXX_STANDARD 14)


#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
#########################################################
# Include Files
#########################################################


########################################################
# Linking & stuff
#########################################################

include_directories(/home/kouushou/glfw-3.3.2/include)
link_directories(/home/kouushou/glfw-3.3.2/_lib/src)
# https://github.com/glfw/glfw/releases/tag/3.3.2
# create the program "test"
add_executable(CG main.cpp)
include_directories(glad/include)
add_library(Glad_lib SHARED glad/src/glad.c)
target_link_libraries(Glad_lib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} dl )

target_link_libraries(CG Glad_lib glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

