cmake_minimum_required(VERSION 3.19.1)

project(myapp 
    VERSION 1.0
    DESCRIPTION "test project"
    LANGUAGES CXX C
)

add_executable(myapp ${SOURCE_FILES})
target_sources(myapp PRIVATE src/main.cpp src/shader.h)

set_target_properties(myapp PROPERTIES
    CMAKE_CXX_STANDARD 14
    CMAKE_CXX_STANDARD_REQUIRED ON
    CMAKE_CXX_FLAGS "-Wfatal-errors -Wall -Werror -Wextra -pedantic -Wno-unused-parameter"
)

#{ GLAD
add_subdirectory(thirdparty/glad)
target_link_libraries(myapp glad)
#}

#{ glfw3 settings
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw-3.3.2)
target_link_libraries(myapp glfw)
#}

#{ OPENGL
find_package(OpenGL REQUIRED)
target_link_libraries(myapp OpenGL::GL)
#}