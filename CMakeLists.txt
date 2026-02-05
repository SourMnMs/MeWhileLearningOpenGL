cmake_minimum_required(VERSION 4.1)
project(FirstOpenGLProj)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp
        glad.c
        Shader.cpp
        Shader.h
        utils/point/Point.cpp
        utils/point/Point.h
        utils/color/Color.cpp
        utils/color/Color.h
        stb_image.cpp
        Camera.cpp
        Camera.h
)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)
