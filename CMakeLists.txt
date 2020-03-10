cmake_minimum_required(VERSION 3.14)
project(RobotOpenGL C)

set(CMAKE_C_STANDARD 99)

add_executable(RobotOpenGL main.c)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(RobotOpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )