
#ifndef SHADER_H
#define SHADER_H

#include "shaders.h"
#include<fstream>
#include<sstream>
#include<iostream>

std::string  GetFileContext(const char* path)
{
   std::string source;
  std::ifstream File;
  
  File.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try{
      File.open(path);
      std::stringstream shaderstream;
      shaderstream << File.rdbuf();
      File.close();
      source = shaderstream.str();
  }
  catch(std::ifstream::failure e ){
        std::cout << "[ERROR] : SHADER::FILE READ OPERTAION INTERUOTED \n" << e.what() << std::endl;
  }
      return source;
}

// shader constructor using shader files using fstream and sstream
    Shader::Shader(const char* vertexPath, const char* fragmentPath){

        std::string vsource = GetFileContext(vertexPath);
        const char* vertexshadersource = vsource.c_str();
        std::string fsource = GetFileContext(fragmentPath);
        const char* fragmentshadersource = fsource.c_str();

        GLuint vertexshader, fragmentshader;

        vertexshader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexshader, 1, &vertexshadersource, NULL);
        glCompileShader(vertexshader);
        CheckErrors(vertexshader, "VERTEX_SHADER");
        
        fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentshader, 1, &fragmentshadersource, NULL);
        glCompileShader(fragmentshader);
        CheckErrors(fragmentshader, "FRAGMENT_SHADER");

        ID = glCreateProgram();
        glAttachShader(ID, vertexshader);
        glAttachShader(ID, fragmentshader);
        glLinkProgram(ID);
        CheckErrors(ID, "SHADER_PROGRAM");

        glDeleteShader(vertexshader);
        glDeleteShader(fragmentshader);
    }


// shader constructor using shader files using fstream and sstream
Shader::Shader(int num, const char* vertexPath, const char* fragmentPath){
        
        std::string source = GetFileContext(vertexPath);
        const char* vertexshadersource = source.c_str();
        source = GetFileContext(fragmentPath);
        const char* fragmentshadersource = source.c_str();

        GLuint vertexshader, fragmentshader; 

        vertexshader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexshader, 1, &vertexshadersource, NULL);
        glCompileShader(vertexshader);
        CheckErrors(num, vertexshader, "VERTEX_SHADER");

        fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentshader, 1, &fragmentshadersource, NULL);
        glCompileShader(fragmentshader);
        CheckErrors(num, fragmentshader, "FRAGMENT_SHADER");

        ID = glCreateProgram();
        glAttachShader(ID, vertexshader);
        glAttachShader(ID, fragmentshader);
        glLinkProgram(ID);
        CheckErrors(num, ID, "SHADER_PROGRAM");

        glDeleteShader(vertexshader);
        glDeleteShader(fragmentshader);
    }


//-----------------------------------------------------------------------------------------

  void Shader::use(){
        glUseProgram(ID);
    }
  void Shader::DeleteProgram(){
        glDeleteShader(ID);
    } 


// values for unifrom values to print colors using fragment shader
  void Shader::setBool(const std::string &name, const bool &r, const bool &g, const bool &b, const bool &a) const{
      glUniform4i(glGetUniformLocation(ID, name.c_str()), (int)r, (int)g, (int)b, (int)a);
  }
  void Shader::setInt(const std::string &name, const int &r, const int &g, const int &b, const int &a) const{
      glUniform4i(glGetUniformLocation(ID, name.c_str()), r, g, b, a);
  }
  void Shader::setFloat(const std::string &name, const float &r, const float &g, const float &b, const float &a) const{
      glUniform4f(glGetUniformLocation(ID, name.c_str()), r, g, b, a);
  }

  void Shader::setBool(const std::string &name, const bool &c) const{
      glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)c);
  }
  void Shader::setInt(const std::string &name, const int &c) const{
      glUniform1i(glGetUniformLocation(ID, name.c_str()), c);
  }
  void Shader::setFloat(const std::string &name, const float &c) const{
      glUniform1f(glGetUniformLocation(ID, name.c_str()), c);
  }


//----------------------------------------------------------------------------------------
// to check errors in shaders and programs 
void Shader::CheckErrors(GLuint shader, std::string type) {

    int success;
    char infoLog[512];

    if(type != "SHADER_PROGRAM"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "[ERROR] : " << type << " FAILED TO COMPILE \n" << infoLog << std::endl
                << "-----------------------------------------------------" << std::endl;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cout << "[ERROR] : SHADER::PROGRAM " << " FAILED TO LINK \n" << infoLog << std::endl
                << "-----------------------------------------------------" << std::endl;
        }
    }
}

void Shader::CheckErrors(int num, GLuint shader, std::string type)
{
    int success;
    char infoLog[512];
    if(type != "SHADER_PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "[ERROR] : " << type << " FAILED TO COMPILE \n" << infoLog << std::endl
                      << "-----------------------------------------------------" << std::endl;
        }
    } else{
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success){
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        std::cout << "[ERROR] : SHADER::PROGRAM " << " FAILED TO LINK \n" << infoLog << std::endl
                  << "-----------------------------------------------------" << std::endl;
        }
    }
}

#endif
