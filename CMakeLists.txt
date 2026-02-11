cmake_minimum_required(VERSION 4.1)
project(FirstOpenGLProj)

set(CMAKE_CXX_STANDARD 20)
set(GLFW_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/glfw/lib/libglfw3.a")
set(GLFW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glfw/include")

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION ${GLFW_LIBRARY_PATH}
        INTERFACE_INCLUDE_DIRECTORIES ${GLFW_INCLUDE_DIR}
)

find_package(OpenGL REQUIRED)

#list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/include/modules")
#find_package(glfw3 REQUIRED)

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