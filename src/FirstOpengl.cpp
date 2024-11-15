

#include <glad/glad.h> // Include GLAD
#include <GLFW/glfw3.h>
#include <iostream>
#include<cmath>

// Vertex Shader source code
const char* vertexShaderSource = " #version 330 core\n"
                                 " layout (location = 0) in vec3 aPos;\n"
                                 " void main()\n"
                                 " {\n"
                                 " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 " }\0";
//Fragment Shader source code 1
const char* fragmentShaderSource1 = " #version 330 core\n"
                                    " uniform vec4 triangleColor;\n"
                                    " out vec4 FragColor;\n"
                                    " void main()\n"
                                    " {\n"
                                    " FragColor = triangleColor;\n"
                                    " }\n\0";
//Fragment Shader source code 2
const char* fragmentShaderSource2 = " #version 330 core\n"
                                    " uniform vec4 triangleColor;\n"
                                    " out vec4 FragColor;\n"
                                    " void main()\n"
                                    " {\n"
                                    " FragColor = triangleColor;\n"
                                    " }\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
 
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "OPENGL", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  if(window == NULL)
  {
    std::cout << "[Error]: Error Creating a window!!" << std::endl;
  }
  
  gladLoadGL();

  glViewport(0, 0, 800, 800);


///-------SHADERS-----------------------------------------


  GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentshader1 = glCreateShader(GL_FRAGMENT_SHADER);
  GLuint fragmentshader2 = glCreateShader(GL_FRAGMENT_SHADER);
  GLuint shaderprogram1 = glCreateProgram();
  GLuint shaderprogram2 = glCreateProgram();
  int success;  char infoLog[512];
  
  glShaderSource(vertexshader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexshader);
  glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(vertexshader, 512, NULL, infoLog);
    std::cout << "VERTEX::SHADER::ERROR::COMPILING::INFOLOG\n" << infoLog << std::endl;
  }

  glShaderSource(fragmentshader1, 1, &fragmentShaderSource1, NULL);
  glCompileShader(fragmentshader1);
  glGetShaderiv(fragmentshader1, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(fragmentshader1, 512, NULL, infoLog);
    std::cout << "FRAGMENT::SHADER::1::ERROR::COMPILING::INFOLOG\n" << infoLog << std::endl;
  }  
  glShaderSource(fragmentshader2, 1, &fragmentShaderSource2, NULL);
  glCompileShader(fragmentshader2);
  glGetShaderiv(fragmentshader2, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(fragmentshader2, 512, NULL, infoLog);
    std::cout << "FRAGMENT::SHADER::2::ERROR::COMPILING::INFOLOG\n" << infoLog << std::endl;
  }
  
  glAttachShader(shaderprogram1, vertexshader);
  glAttachShader(shaderprogram1, fragmentshader1);
  glLinkProgram(shaderprogram1);
  glGetProgramiv(shaderprogram1, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(shaderprogram1, 512, NULL, infoLog);
    std::cout << "SHADER::PROGRAM::1::ERROR::LINKING::INFOLOG\n" << infoLog << std::endl; 
  }
  glAttachShader(shaderprogram2, vertexshader);
  glAttachShader(shaderprogram2, fragmentshader2);
  glLinkProgram(shaderprogram2);
  glGetProgramiv(shaderprogram2, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(shaderprogram2, 512, NULL, infoLog);
    std::cout << "SHADER::PROGRAM::2::ERROR::LINKING::INFOLOG\n" << infoLog << std::endl; 
  }
  glDeleteShader(vertexshader);
  glDeleteShader(fragmentshader1);
  glDeleteShader(fragmentshader2);

  GLfloat vertices[9] = {
      -0.5f, 0.5f, 0.0f,
       0.0f, 0.5f, 0.0f,
      -0.5f, 0.0f, 0.0f
  };
  GLfloat t_vertices[9] = {
    //second triangle
      0.5f, -0.5f, 0.0f,
      0.0f, -0.5f, 0.0f,
      0.5f,  0.0f, 0.0f
  };

  GLuint indices[3] = {
     0, 1, 2 
  };


  GLuint VBO[2], VAO[2], EBO[2];
  glGenVertexArrays(2, &VAO[0]);
  glGenBuffers(2, &VBO[0]);
  glGenBuffers(2, &EBO[0]);
  
  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertices), t_vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  //GLint unicolor1 = glGetUniformLocation(shaderprogram1, "triangleColor");
  //GLint unicolor2 = glGetUniformLocation(shaderprogram2, "triangleColor");
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//----------LOOP-FOR-PRINTING-------------------------------

  while(!glfwWindowShouldClose(window))
  {
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderprogram1);
    GLfloat time = glfwGetTime();
    //std::cout << "Time = " << time << std::endl;
    GLfloat redvalue = sin(time)/ 2.0f + 0.6f;
    GLint vertexcolorlocation1 = glGetUniformLocation(shaderprogram1, "triangleColor");  
    glUniform4f(vertexcolorlocation1, redvalue, 0.0f, 0.0f, 1.0f);  
    glBindVertexArray(VAO[0]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); 
   
    glUseProgram(shaderprogram2);
    GLfloat time2 = glfwGetTime();
    GLfloat colorvalue = (sin(time2) / 2.0f) + 0.6f;
    GLint vertexcolorlocation2 = glGetUniformLocation(shaderprogram2 ,"triangleColor");
    glUniform4f(vertexcolorlocation2, 0.0f, 0.0f, colorvalue, 1.0f);
    glBindVertexArray(VAO[1]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  

  glDeleteVertexArrays(2, VAO);
  glDeleteBuffers(2, VBO);
  glDeleteBuffers(2, EBO);
  glDeleteProgram(shaderprogram1);
  glDeleteProgram(shaderprogram2);
  glfwDestroyWindow(window);
  glfwTerminate();
}



