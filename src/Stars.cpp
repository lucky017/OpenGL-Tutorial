

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Headers/shaders.h"
#define STB_IMAGE_IMPLEMENTATION


#define WIDTH  800
#define HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "TEXTURE", NULL, NULL);
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   if(!window)
   {
      std::cout << "[ERROR] LOADING WINDOW " << std::endl;
   }
   //important
   gladLoadGL();
  
   GLfloat vertices[] = {
//            Vertices                     Colors
         0.00f,  0.50f, 0.0f,/*A0*/   0.5f, 0.0f, 0.0f,
        -0.50f,  0.25f, 0.0f,/*B1*/   0.0f, 0.5f, 0.0f,
        -0.30f, -0.50f, 0.0f,/*C2*/   0.0f, 0.0f, 0.5f,
         0.30f, -0.50f, 0.0f,/*D3*/   0.2f, 0.0f, 0.0f,
         0.50f,  0.25f, 0.0f,/*E4*/   0.0f, 0.2f, 0.0f,
        -0.10f,  0.10f, 0.0f,/*F5*/   0.0f, 0.0f, 0.2f,
         0.10f,  0.10f, 0.0f,/*G6*/   1.0f, 0.0f, 0.0f,
        -0.20f,  0.00f, 0.0f,/*H7*/   0.0f, 1.0f, 0.0f,
         0.20f,  0.00f, 0.0f,/*I8*/   0.0f, 0.0f, 1.0f,
         0.00f, -0.25f, 0.0f,/*J9*/   1.0f, 1.0f, 1.0f
  };
  GLuint index[15] = {
      0, 2, 8,//ACI
      0, 3, 7,//ADH
      2, 4, 5,//CEF
      1, 3, 6,//BDG
      1, 4, 9//BEJ
   };

   Shader shader("/home/lucky/opengl/src/Shaders/vertexshader.vs", "/home/lucky/opengl/src/Shaders/fragmentshader.fs");
   
   GLuint VAO, VBO, EBO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1,&VBO);
   glGenBuffers(1, &EBO);

   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(3);


   while(!glfwWindowShouldClose(window))
   {
      glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
     
      shader.use();
      
      glDrawElements(GL_TRIANGLES, 15 , GL_UNSIGNED_INT, 0);
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   shader.DeleteProgram();
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);
   glDeleteVertexArrays(1, &VAO);

   glfwDestroyWindow(window);
   glfwTerminate();
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}
