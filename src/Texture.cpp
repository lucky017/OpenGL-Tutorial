

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Headers/shaders.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Headers/stb_image.h"

#define WIDTH 800
#define HEIGHT 800

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
      //       vertices             Textures
            -1.0f,  1.0f, 0.0f,     1.0f, 1.0f,    0.5f, 0.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,     1.0f, 0.0f,    0.0f, 0.5f, 0.0f,
             1.0f, -1.0f, 0.0f,     0.0f, 0.0f,    0.0f, 0.0f, 0.5f,
             1.0f,  1.0f, 0.0f,     0.0f, 1.0f,    0.5f, 0.0f, 0.5f
   };
   GLuint index[] = {
      0, 1, 2,
      0, 2, 3
   };
   
   Shader shader("/home/lucky/opengl/src/Shaders/Texture.vs", "/home/lucky/opengl/src/Shaders/Texture.fs");
   
   GLuint VAO, VBO, EBO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1,&VBO);
   glGenBuffers(1, &EBO);

   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(2);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
   glEnableVertexAttribArray(1);

   GLuint texture;
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   int width, height, nrChannels;
   unsigned char* data = stbi_load("/home/lucky/opengl/src/Resources/Textures/container.jpg", &width, &height, &nrChannels, 0);
   if(data)
   {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
   }
   else{
      std::cout << "[ERROR]:: LOADING TEXTURE" << std::endl;
   }

   stbi_image_free(data);
   

   while(!glfwWindowShouldClose(window))
   {
      glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
     
      glBindTexture(GL_TEXTURE_2D, texture);
      shader.use();
      
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   shader.DeleteProgram();
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);
   glDeleteTextures(1, &texture);
   glDeleteVertexArrays(1, &VAO);

   glfwDestroyWindow(window);
   glfwTerminate();
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}
