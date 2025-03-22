

#include "../../Include/shaders.h"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../../Include/stb_image.h"


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
      //       vertices                 Colors           Texture1       Texture2
            -1.0f,  1.0f, 0.0f,    0.5f, 0.0f, 0.0f,     1.0f, 1.0f,    -2.0f, 2.0f,
            -1.0f, -1.0f, 0.0f,    0.0f, 0.5f, 0.0f,     1.0f, 0.0f,    -2.0f, -2.0f,
             1.0f, -1.0f, 0.0f,    0.0f, 0.0f, 0.5f,     0.0f, 0.0f,    2.0f, -2.0f,
             1.0f,  1.0f, 0.0f,    0.5f, 0.0f, 0.5f,     0.0f, 1.0f,    2.0f, 2.0f
   };
   GLuint index[] = {
      0, 1, 2,
      0, 2, 3
   };
   
   Shader shader("Textures/Mirror_repeat.vs", "Textures/Mirror_repeat.fs");
   
   GLuint VAO, VBO, EBO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1,&VBO);
   glGenBuffers(1, &EBO);

   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(6 * sizeof(float)));
   glEnableVertexAttribArray(2);
   glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));
   glEnableVertexAttribArray(3);

   GLuint texture1;
   glGenTextures(1, &texture1);
   glBindTexture(GL_TEXTURE_2D, texture1);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   stbi_set_flip_vertically_on_load(true);
   int width, height, nrChannels;
   unsigned char* data1 = stbi_load("/home/lucky/opengl/Resources/Textures/wall.jpg", &width, &height, &nrChannels, 0);
   if(data1)
   {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
      glGenerateMipmap(GL_TEXTURE_2D);
   }
   else{
      std::cout << "[ERROR]:: LOADING TEXTURE" << std::endl;
   }
   if(data1){
      stbi_image_free(data1);
   }

   GLuint texture2;
   glGenTextures(1, &texture2);
   glBindTexture(GL_TEXTURE_2D, texture2);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    unsigned char* data2 = stbi_load("/home/lucky/opengl/Resources/cat3.jpg", &width, &height, &nrChannels, 0);
   if(data2){
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
      glGenerateMipmap(GL_TEXTURE_2D);
   }
   else{
      std::cout << "second Textutre got error Check it out " << std::endl;
   }
   if(data2){
      stbi_image_free(data2);
   }


   shader.use();
   shader.setInt("Texture1", 0);
   shader.setInt("Texture2", 1);
   
   while(!glfwWindowShouldClose(window))
   {
      glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
     
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
     
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   shader.DeleteProgram();
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);
   glDeleteVertexArrays(1, &VAO);
   glDeleteTextures(1, &texture1);
   glDeleteTextures(1, &texture2);
   glfwDestroyWindow(window);
   glfwTerminate();
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}
