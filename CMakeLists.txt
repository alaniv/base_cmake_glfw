cmake_minimum_required(VERSION 3.0)

project(myapp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw-3.3.2)

set(SOURCE_FILES src/main.cpp src/shader.h thirdparty/glad/src/glad.c)
add_executable(myapp ${SOURCE_FILES})
target_include_directories(myapp PRIVATE thirdparty/glad/include)

target_link_libraries(myapp glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(myapp OpenGL::GL)


#set(LIBS glfw3 opengl32 gdi32)

#CFLAGS=-std=c++14 -Wfatal-errors -Wall -Werror -Wextra -pedantic -Wno-unused-parameter
