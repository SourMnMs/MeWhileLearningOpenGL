cmake_minimum_required(VERSION 4.1)
project(FirstOpenGLProj)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if (DEFINED glfw3_DIR)
    message(STATUS "FOUND GLFW3: ${glfw3_DIR}")
else()
    message(STATUS "UH-OH: glfw3_DIR NOT FOUND")
endif()

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