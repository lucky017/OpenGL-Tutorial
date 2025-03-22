
#include "../../Include/shaders.h"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../../Include/stb_image.h"
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#define WIDTH 800
#define HEIGHT 800

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
float Color();

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
      //       vertices                   colors            Textures
            -1.0f,  1.0f, 0.0f,     1.0f, 1.0f, 1.0f,    //1.0f, 1.0f,
            -1.0f, -1.0f, 0.0f,     1.0f, 1.0f, 1.0f,    //1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,     1.0f, 1.0f, 1.0f,    //0.0f, 0.0f,
             1.0f,  1.0f, 0.0f,     1.0f, 1.0f, 1.0f     //0.0f, 1.0f
   };
   GLuint index[] = {
      0, 1, 2,
      0, 2, 3
   };
   
   Shader shader("Transformations/Movement.vs", "Transformations/Movement.fs");
   
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
   glEnableVertexAttribArray(1);

   shader.use();
   GLint Location;
   glm::mat4 view = glm::scale(glm::mat4(1.0f), glm::vec3(0.20f, 0.20f, 0.0f));
   view = glm::translate(view, glm::vec3(-4.0f, 1.0f, 0.0f));
   Location = shader.location("object");
   glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(view));

   glm::mat4 move(1.0f);
   while(!glfwWindowShouldClose(window))
   {
      float movement = 0.0f;
      glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      shader.setFloat("Colors", 1.0f, 1.0f, 1.0f, 1.0f);
      if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      {
         movement += 1.0f;
      }

      move = glm::translate(move, glm::vec3(movement, 0.0f, 0.0f));
      Location = shader.location("movement");
      glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(move));

      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

float Color()
{
   float time = glfwGetTime();
   float value = (sin(time)/1.5f) + 1.0f;
   return value;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}
