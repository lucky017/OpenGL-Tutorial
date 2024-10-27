


#include <glad/glad.h> // Include GLAD
#include <GLFW/glfw3.h>
#include <iostream>


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.9f, 0.17f, 0.11f, 1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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
  GLfloat vertices[12] = {
       0.5f,  0.5f, 0.0f,  //top-right    
      -0.5f,  0.5f, 0.0f,  //top-left    
       0.5f, -0.5f, 0.0f,  //bottom-right 
      -0.5f, -0.5f, 0.0f   //bottom-left 
  };

  GLuint indices[6] = {
      0, 3, 2,
      0, 1, 3
  };
  glViewport(0, 0, 800, 800);


///-------SHADERS-----------------------------------------


  GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexshader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexshader);
  
  int success;
  char infoLog[512];
  glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(vertexshader, 512, NULL, infoLog);
    std::cout << "VERTEX::SHADER::ERROR::COMPILING::INFOLOG\n" << infoLog << std::endl;
  }

  GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentshader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentshader);
  glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(fragmentshader, 512, NULL, infoLog);
    std::cout << "FRAGMENT::SHADER::ERROR::COMPILING::INFOLOG\n" << infoLog << std::endl;
  }

  GLuint shaderprogram = glCreateProgram();
  glAttachShader(shaderprogram, vertexshader);
  glAttachShader(shaderprogram, fragmentshader);
  glLinkProgram(shaderprogram);

  glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(shaderprogram, 512, NULL, infoLog);
    std::cout << "SHADER::PROGRAM::ERROR::LINKING::INFOLOG\n" << infoLog << std::endl; 
  }
  glDeleteShader(vertexshader);
  glDeleteShader(fragmentshader);


  GLuint VBO, VAO, EBO;
  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);



  while(!glfwWindowShouldClose(window))
  {
    processInput(window);
    glClearColor(0.15f, 0.56f, 0.90f, 0.46f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderprogram);
    glBindVertexArray(VAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
    glBindVertexArray(0);


    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderprogram);
  glfwDestroyWindow(window);
  glfwTerminate();
}



