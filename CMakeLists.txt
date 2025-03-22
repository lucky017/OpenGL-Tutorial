
cmake_minimum_required(VERSION 3.30.0)
project(OpenGL)

SUBDIRS(
     Implementation 
     Library 
     Scripts
)

# Find OpenGL
if(POLICY CMP0072)
cmake_policy(SET CMP0072 NEW)
endif()
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(glfw3 REQUIRED)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)
add_executable(opengl ${CMAKE_SOURCE_DIR}/Scripts/${SOURCE_FILE_PATH})

target_link_directories(opengl PRIVATE 
     PUBLIC ${CMAKE_SOURCE_DIR}/Implementation/
     PUBLIC ${CMAKE_SOURCE_DIR}/Library/
     )

target_link_libraries(
    opengl
    Implementation
    glad 
    glfw
    dl
    )
if(TARGET Implementation)
    target_link_libraries(opengl Implementation)
endif()
