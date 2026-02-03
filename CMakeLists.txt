cmake_minimum_required(VERSION 3.5)
project(graphics VERSION 0.1.0)

cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)

add_executable(graphics 
    src/main.cpp
    src/glad.h
    src/glad.c
)

target_include_directories(graphics PRIVATE src)

target_link_libraries(graphics 
    glfw
    OpenGL::GL
    ${CMAKE_DL_LIBS}
)
