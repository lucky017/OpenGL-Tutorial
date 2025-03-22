
option(ENABLE_SHADER_SOURCE_FILE "Option to Enable or Disable the shader source file" ON)

if(ENABLE_SHADER_SOURCE_FILE)
    set(SHADER_SOURCE_FILE "" CACHE STRING "Need a Shader Source File to Compile")
endif()

if(ENABLE_SHADER_SOURCE_FILE AND NOT SHADER_SOURCE_FILE)
    message(FATAL_ERROR "Please specify the SHADER SOURCE FILE using 
            -DSHADER_SOURCE_FILE=<filname>")
endif()

if(ENABLE_SHADER_SOURCE_FILE)
    add_library(Implementation STATIC "./${SHADER_SOURCE_FILE}" )
endif()
