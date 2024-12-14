


#include "../Headers/shaders.h"

std::string GetFileContext(const char* path)
{
    return "ERROR - Check the header file again";
}


// shaders constructor for normal infile shader sources
Shader::Shader(std::string &vertex, std::string &fragment)
{
  const char* vertexshadersource = vertex.c_str();
  const char* fragmentshadersource = fragment.c_str();
  GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexshader, 1, &vertexshadersource, NULL);
  glCompileShader(vertexshader);
  CheckErrors(vertexshader, "VERTEX_SHADER");

  GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
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

Shader::Shader(int num, std::string &vertex, std::string &fragment)
{
  const char* vertexshadersource = vertex.c_str();
  const char* fragmentshadersource = fragment.c_str();
  GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexshader, 1, &vertexshadersource, NULL);
  glCompileShader(vertexshader);
  CheckErrors(num, vertexshader, "VERTEX_SHADER");

  GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
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
        glDeleteProgram(ID);
    } 


// values for unifrom values to print colors using fragment shader
void Shader::setBool(const std::string &name, const bool &r, const bool &g, const bool &b, const bool &a) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform4i(location, static_cast<int>(r), static_cast<int>(g), static_cast<int>(b), static_cast<int>(a));
    }
}
void Shader::setInt(const std::string &name, const int &r, const int &g, const int &b, const int &a) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform4i(location, r, g, b, a);
    }
}
void Shader::setFloat(const std::string &name, const float &r, const float &g, const float &b, const float &a) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform4f(location, r, g, b, a);
    }
}

  void Shader::setBool(const std::string &name, const bool &c) const{
     GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform1i(location, static_cast<int>(c));
    }
  }
  void Shader::setInt(const std::string &name, const int &c) const{
      GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform1i(location, c);
    }
  }
  void Shader::setFloat(const std::string &name, const float &c) const{
       GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform1f(location, c);
    }
  }


//----------------------------------------------------------------------------------------
// to check errors in shaders and programs 
void Shader::CheckErrors(GLuint shader, std::string type) {

    int success;
    char infoLog[512];

    if(type != "PROGRAM"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "[ERROR] : " << type <<"::SHADER " << " FAILED TO COMPILE \n" << infoLog << std::endl
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
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "[ERROR] : " << type <<"::SHADER " << num << " FAILED TO COMPILE \n" << infoLog << std::endl
                      << "-----------------------------------------------------" << std::endl;
        }
    } else{
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success){
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        std::cout << "[ERROR] : SHADER::PROGRAM " << num << " FAILED TO LINK \n" << infoLog << std::endl
                  << "-----------------------------------------------------" << std::endl;
        }
    }
}


