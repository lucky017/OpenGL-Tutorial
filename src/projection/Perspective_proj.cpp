

#include "../Headers/shaders.h"
#include<GLFW/glfw3.h>
#include<cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "../Headers/stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define WIDTH 1366.0f
#define HEIGHT 768.0f

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
   if(!window){
      std::cout << "Issue with creating the opengl window using GLFW" << std::endl;
      return -1;
   }
   gladLoadGL();  
   Shader shader("/home/lucky/opengl/src/Shaders/Projections.vert","/home/lucky/opengl/src/Shaders/Projections.frag");
   
   GLfloat vertices[] = {
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
   };
   glm::vec3 cubePositions[10] = {
      glm::vec3( 0.0f,  0.0f,  0.0f),
      glm::vec3( 2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3( 2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3( 1.3f, -2.0f, -2.5f),
      glm::vec3( 1.5f,  2.0f, -2.5f),
      glm::vec3( 1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
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
   if(data){
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      } else{
      std::cout << "Texture Loading Error at STB_IMAGE_LOAD();" << std::endl;
      }
   stbi_image_free(data);
   shader.use();
   
   while(!glfwWindowShouldClose(window))
   {
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glEnable(GL_DEPTH_TEST);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      GLfloat n = glfwGetTime();
      static float startTime = glfwGetTime();
      float a = glfwGetTime() - startTime;
      if (a > 4.5f) {
         startTime = glfwGetTime();
      }
      std::cout << "TIME = " << a << ";\n";
      
      glm::mat4 view = glm::mat4(1.0f);
      view = glm::translate(view, glm::vec3(a * 0.0f, a * 0.0f, a * -2.0f));
      glm::mat4 projection = glm::perspective(glm::radians(40.0f), WIDTH / HEIGHT, 0.1f, 100.0f);
      
      GLint Location;
      Location = shader.location("view");
      glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(view));
      Location = shader.location("projection");
      glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(projection));
      
      for(GLuint i=0; i<10; i++)
      {
         glm::mat4 model = glm::mat4(1.0f);
         model = glm::translate(model, cubePositions[i]);
         GLfloat angle = 40.0f * i;
         // if(i % 3 ==0)
         //    angle = glfwGetTime() * 25.0f;
         model = glm::rotate(model, n * glm::radians(angle), glm::vec3(-0.3f, 0.05f, 0.5f));
         Location = shader.location("model");
         glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(model));
         
         glDrawArrays(GL_TRIANGLES, 0, 36);
      }
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
float paint()
{
   double time = glfwGetTime();
   return sin(time)/ 2.0f;
}
