

set(SOURCE_FILE_PATH "" CACHE STRING "Need a Source File to Complile")
if(NOT SOURCE_FILE_PATH)
    message(FATAL_ERROR "Please provide a valid source file using 
            -DSOURCE_FILE_PATH=<folder>/<filename>")
endif()


#add_subdirectory(opengl)
