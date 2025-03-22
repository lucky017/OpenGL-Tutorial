

add_library(glad "./src/glad.c" "./glad/glad.h")
target_include_directories(glad PUBLIC "${CMAKE_SOURCE_DIR}/Include/")
