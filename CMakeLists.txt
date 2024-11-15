



cmake_minimum_required(VERSION 3.10)
project(OpenGL VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)

# Add glad
include_directories(${PROJECT_SOURCE_DIR}/glad/include)
file(GLOB SOURCES "glad/src/glad.c")

# Add your source files
file(GLOB_RECURSE APP_SOURCES "src/*.cpp")

# Find OpenGL
if(POLICY CMP0072)
cmake_policy(SET CMP0072 NEW)
endif()
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(glfw3 REQUIRED)
add_subdirectory(glad)

# Create the executable
add_executable(OpenGL ${SOURCES} ${APP_SOURCES})

# Link libraries
target_link_libraries(
    OpenGL PUBLIC
    glfw
    glad
    dl
)

