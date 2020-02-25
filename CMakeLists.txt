cmake_minimum_required(VERSION 3.10)
project(Projet C)

set(CMAKE_C_STANDARD 99)

add_executable(Projet main.c main.c)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(Projet ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
message("opengl glut: " ${OPENGL_LIBRARIES}" " ${GLUT_LIBRARY} )
SET(GCC_EXE "-Wall -W -Wextra -no-pie")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_EXE}")

message(${GCC_EXE})
message(${CMAKE_C_FLAGS})