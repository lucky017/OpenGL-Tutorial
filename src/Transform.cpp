

#include "Headers/shaders.h"
#include<GLFW/glfw3.h>
#include<cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "Headers/stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define WIDTH 800
#define HEIGHT 800

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
float paint();

int main()
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "TRANSFORM", NULL, NULL);
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   if(!window)
   {
      std::cout << "Issue with creating the opengl window using GLFW" << std::endl;
      return -1;
   }
   gladLoadGL();  //important to load glad functions to use

   Shader shader("/home/lucky/opengl/src/Shaders/Transform.vert","/home/lucky/opengl/src/Shaders/Transform.frag");

   GLfloat vertices[] = {
      -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
      -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
       0.6f, -0.5f, 0.0f,  1.0f, 0.0f,
       0.6f,  0.5f, 0.0f,  1.0f, 1.0f
   };
   GLuint index[] = {
      0, 1, 2,
      0, 2, 3
   };
   
   GLuint VAO, VBO, EBO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);
   
   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0); 
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(2);

   GLuint texture;
   glGenBuffers(1, &texture);
   glBindBuffer(GL_TEXTURE_2D, texture);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   stbi_set_flip_vertically_on_load(true);
   int w, h, n;
   unsigned char* data = stbi_load("/home/lucky/opengl/src/Resources/cat3.jpg", &w, &h, &n, 0);
   if(data)
   {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
   }
   else{
      std::cout << "Texture Loading Error at STB_IMAGE_LOAD();" << std::endl;
   }
   
   stbi_image_free(data);
   shader.use();
    
   while(!glfwWindowShouldClose(window))
   {
      glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glm::mat4 trans = glm::mat4(1.0f);
      GLfloat n = (GLfloat)glfwGetTime();
      //trans = glm::translate(trans, glm::vec3(n * 0.1f, n*0.1f, n*0.1f));
      trans = glm::rotate(trans,n * glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));

      //trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
      GLint Location = glGetUniformLocation(shader.ID, "transform");
      glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(trans));

      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}
float paint()
{
   double time = glfwGetTime();
   return sin(time)/ 2.0f;
}
