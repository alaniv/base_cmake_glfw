cmake_minimum_required(VERSION 3.19.1)

project(myapp 
    VERSION 1.0
    DESCRIPTION "test project"
    LANGUAGES CXX C
)

add_executable(myapp)
target_sources(myapp PRIVATE src/main.cpp 
src/Shader.cpp 
src/window.cpp 
src/Mesh.cpp
src/Camera.cpp
src/Texture.cpp
)

set_target_properties(myapp PROPERTIES
    CMAKE_CXX_STANDARD 14
    CMAKE_CXX_STANDARD_REQUIRED ON
    CMAKE_CXX_EXTENSIONS OFF
    CMAKE_CXX_FLAGS "-Wfatal-errors -Wall -Werror -Wextra -pedantic"
)
target_compile_features(myapp PRIVATE cxx_std_14)

#{ GLAD
add_subdirectory(thirdparty/glad)
target_link_libraries(myapp glad)
#}

#{ GLM
add_subdirectory(thirdparty/glm-master)
target_link_libraries(myapp glm)
#}

#{ STB
add_subdirectory(thirdparty/stb)
target_link_libraries(myapp stb)
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

#{ GOOGLE TEST MOCK
add_subdirectory(thirdparty/googletest-master)
target_link_libraries(myapp gmock)
target_link_libraries(myapp gtest)

enable_testing()
add_executable(runUnitTests)
target_sources(runUnitTests PRIVATE test/testExample.cpp)
target_link_libraries(runUnitTests gtest gtest_main)
#}

#{ assimp settings
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_INSTALL_PDB OFF)
add_subdirectory(thirdparty/assimp-master)
target_link_libraries(myapp assimp)
#}
