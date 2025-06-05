
#pragma once


#ifndef SHADERS_H
#define SHADERS_H

#include<glad/glad.h>
#include <string>
#include<iostream>

std::string GetFileContext(const char* path);

struct Shader
{
public:
    GLuint ID; 
    Shader(const char* vertexshaderpath, const char* fragmentshaderpath);
    Shader(int num, const char* vertexshaderpath, const char* fragmentshaderpath);
    
    Shader(std::string  &vertexshadersource, std::string &fragmentshadersource);
    Shader(int num, std::string &vertexshadersource, std::string &fragmentshadersource);


    void setBool(const std::string &name, const bool &r, const bool &g, const bool &b, const bool a) const;
    void setBool(const std::string &name, const bool &c) const;

    void setInt(const std::string &name, const int &r, const int &g, const int &b, const int a) const;
    void setInt(const std::string &name, const int &c) const;

    void setFloat(const std::string &name, const float &r, const float &g, const float &b, const float a) const;
    void setFloat(const std::string &name, const float &c) const;
    
    void CheckErrors(GLuint shader, std::string type);
    void CheckErrors(int num, GLuint shader, std::string type);
    void use();
    void DeleteProgram();
    unsigned int location(const char* name);

    void CreateVertexShader(const char* vertexshaderpath);
    void CreateFragmentShader(const char* fragmentshaderpath);
};

#endif
