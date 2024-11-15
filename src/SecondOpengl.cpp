

#include <glad/glad.h> // Include GLAD
#include <GLFW/glfw3.h>
#include <iostream>
#include<cmath>
#include "source.h"


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

  glViewport(0, 0, 800, 800);


///-------SHADERS-----------------------------------------

  Shader shader1(1, "/home/lucky/opengl/src/shaders/vertexshader.vs", "/home/lucky/opengl/src/shaders/fragmentshader_1.fs");
  Shader shader2(2, "/home/lucky/opengl/src/shaders/vertexshader.vs", "/home/lucky/opengl/src/shaders/fragmentshader_2.fs");
  
  GLfloat vertices[] = {
          //vertices            //colors
      -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
       0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 0.0f,
      -0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f
  };
  GLfloat t_vertices[] = {
          //vertices          //colors
      -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
       0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 0.0f,
       0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f
  };

  GLuint indices[] = {
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3* sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertices), t_vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  //GLint unicolor1 = glGetUniformLocation(shaderprogram1, "triangleColor");
  //GLint unicolor2 = glGetUniformLocation(shaderprogram2, "triangleColor");
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//----------LOOP-FOR-PRINTING-------------------------------

  while(!glfwWindowShouldClose(window))
  {
    processInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    GLdouble time_1 = glfwGetTime();
    GLfloat r_1value = sin(time_1) / 2.0f + 1.0f;
    GLfloat g_1value = sin(time_1) / 2.0f + 0.2f;
    GLfloat b_1value = sin(time_1 + 1.0f) / 2.0f + 0.3f; 
    glClear(GL_COLOR_BUFFER_BIT);
    shader1.use(); 
    shader1.setFloat("ourColor", r_1value, g_1value, b_1value);
    glBindVertexArray(VAO[0]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); 
   
    GLfloat time_2 = glfwGetTime();
    GLfloat r_2value = sin(time_2) / 2.0f + 0.3f;
    GLfloat g_2value = sin(time_2) / 2.0f + 0.2f;
    GLfloat b_2value = sin(time_2) / 2.0f + 1.0f;
    shader2.use();
    shader1.setFloat("ourColor", r_2value, g_2value, b_2value);  
    glBindVertexArray(VAO[1]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  

  glDeleteVertexArrays(2, VAO);
  glDeleteBuffers(2, VBO);
  glDeleteBuffers(2, EBO);
  shader1.DeleteProgram();
  shader2.DeleteProgram();
  glfwDestroyWindow(window);
  glfwTerminate();
}



