cmake_minimum_required(VERSION 3.24)
project(cube C)

set(CMAKE_C_STANDARD 11)

add_executable(cube src/main.c src/gl_error.c)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

add_subdirectory(lib/glew-2.2.0/build/cmake)
add_subdirectory(lib/glfw-3.3.8)

target_link_libraries(cube OpenGL::GL)
target_link_libraries(cube glew)
target_link_libraries(cube glfw)

include_directories(lib/cube/include)
include_directories(lib/glew-2.2.0/include)
include_directories(lib/glfw-3.3.8/include)
