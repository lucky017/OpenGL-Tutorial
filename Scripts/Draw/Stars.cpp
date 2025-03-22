

#include "../../Include/shaders.h"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION

#if !defined(WIDTH) || !defined(HEIGHT)
#define WIDTH 1380
#define HEIGHT 720
#endif


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
  
GLfloat vertices[10 * 6] = {
    // Vertices                   Colors
    0.00f, 0.50f, 0.0f,          0.5f, 0.0f, 0.0f,  // Top point (A0)
   -0.15f, 0.10f, 0.0f,          0.0f, 0.5f, 0.0f,  // Inner left (B1)
    0.15f, 0.10f, 0.0f,          0.0f, 0.0f, 0.5f,  // Inner right (C2)
   -0.50f, 0.15f, 0.0f,          0.2f, 0.0f, 0.0f,  // Outer left point (D3)
    0.50f, 0.15f, 0.0f,          0.0f, 0.2f, 0.0f,  // Outer right point (E4)
   -0.20f,-0.25f, 0.0f,          0.0f, 0.0f, 0.2f,  // Mid left (F5)
    0.20f,-0.25f, 0.0f,          1.0f, 0.0f, 0.0f,  // Mid right (G6)
   -0.30f,-0.70f, 0.0f,          0.0f, 1.0f, 0.0f,  // Bottom left point (H7)
    0.30f,-0.70f, 0.0f,          0.0f, 0.0f, 1.0f,  // Bottom right point (I8)
    0.00f,-0.40f, 0.0f,          1.0f, 1.0f, 1.0f   // Bottom inner point (J9)
};

GLuint index[8*3] = {
    0, 1, 2,    // Top triangle
    3, 1, 5,    // Left upper arm
    2, 4, 6,    // Right upper arm
    1, 5, 6,    // Middle section left part
    1, 2, 6,    // Middle section right part
    5, 6, 9,    // Center bottom section
    5, 7, 9,    // Left bottom arm
    9, 6, 8     // Right bottom arm
};

   Shader shader("Draw/Stars.vs", "Draw/Stars.fs");
   
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

   
   shader.use();
   while(!glfwWindowShouldClose(window))
   {
      processInput(window);
      glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
           
      glDrawElements(GL_TRIANGLES, 24 , GL_UNSIGNED_INT, 0);
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

void processInput(GLFWwindow* window)
{
   if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
      glfwSetWindowShouldClose(window, true);
   }
}
