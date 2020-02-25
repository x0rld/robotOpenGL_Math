cmake_minimum_required(VERSION 3.10)
project(RobotOpenGL C)

set(CMAKE_C_STANDARD 99)

add_executable(RobotOpenGL main.c main.c)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
if (UNIX)
    target_link_libraries(RobotOpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} -lm )
else()
    target_link_libraries(RobotOpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif ()

message("opengl glut: " ${OPENGL_LIBRARIES}" " ${GLUT_LIBRARY} )
if(UNIX)
SET(GCC_EXE "-Wall -Wextra -no-pie")
else()
    SET(GCC_EXE "-Wall -Wextra")
endif()
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_EXE}")

message(${GCC_EXE})
message(${CMAKE_C_FLAGS})