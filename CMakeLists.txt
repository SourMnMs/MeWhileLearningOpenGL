cmake_minimum_required(VERSION 4.1)
project(FirstOpenGLProj)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/include/modules")
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp
        glad.c
        Shader.cpp
        Shader.h
        stb_image.cpp
        Camera.cpp
        Camera.h
        Shapes/Shape.cpp
        Shapes/Shape.h
        bufferLog.cpp
        bufferLog.h
        utils/CoordinateSystem/CoordinateSystem.cpp
        utils/CoordinateSystem/CoordinateSystem.h
)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)