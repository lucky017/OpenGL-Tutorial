
#include "../../Include/shaders.h"
#include<GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/glm.hpp>


#define WIDTH 1380.0f
#define HEIGHT 780.0f

const double GRAVITY = -9.800000f * (1/300.0f);
//float PLAYER_Y = 0.5f;

glm::vec3 CAMERA_POSITION(0.0f, 1.2f, 3.0f);
glm::vec3 DIRECTION_VECTOR(0.0f, 0.0f, -1.0f);
glm::vec3 UP_VECTOR(0.0f, 1.0f, 0.0f);
glm::vec3 PLAYER(0.0f, 0.5f, 0.0f);
glm::vec3 GROUND(100.0f, 0.0f, 100.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void InputProcess(GLFWwindow* window);


int main()
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   GLFWwindow* window = glfwCreateWindow((int)WIDTH, (int)HEIGHT, "FIRST-PERSON", NULL, NULL);
   if(!window){
      std::cout << "COULDN'T CREATE THE OPENGL WINDOW!! CHECK FOR ERRORS\n";
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   gladLoadGL();

   const GLfloat vertices[8 * 3] = {
      0.5f,  0.5f,  0.5f,
     -0.5f, -0.5f,  0.5f,
     -0.5f,  0.5f, -0.5f,
     -0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      };
   const GLuint index[12 * 3] = {
      0, 2, 3, 0, 2, 4,
      1, 2, 3, 1, 2, 5,
      1, 5, 6, 1, 6, 7,
      0, 6, 7, 0, 6, 4,
      0, 1, 3, 0, 1, 7,
      2, 4, 5, 4, 5, 6
      }; 


   Shader shader("Camera/SimpleGame.vs", "Camera/SimpleGame.fs");
   
   GLuint VAO, VBO, EBO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);
   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   shader.use();
   glEnable(GL_DEPTH_TEST);

   while(!glfwWindowShouldClose(window)){
      
      InputProcess(window);
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      glm::mat4 model = glm::mat4(1.0f);
      glm::mat4 view = glm::mat4(1.0f);
      glm::mat4 projection = glm::mat4(1.0f);
      PLAYER.y += GRAVITY;
      if(PLAYER.y < 0.5f)
         PLAYER.y = 0.5f;
      
      model = glm::translate(model, PLAYER);
      glUniformMatrix4fv(shader.location("Model"), 1, GL_FALSE, glm::value_ptr(model));
      view = glm::lookAt( CAMERA_POSITION, DIRECTION_VECTOR, UP_VECTOR );
      glUniformMatrix4fv(shader.location("View"), 1, GL_FALSE, glm::value_ptr(view));
      projection = glm::perspective(glm::radians(60.0f), WIDTH/HEIGHT , 0.1f, 100.0f);
      glUniformMatrix4fv(shader.location("Projection"), 1, GL_FALSE, glm::value_ptr(projection));
       
      glUniform3f(shader.location("COLOR"), 0.6f, 0.1f, 0.1f);
      //glBindVertexArray(VAO);
      //glDrawArrays(GL_TRIANGLES, 0, 36);
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
      
      model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 4.0f));
      model = glm::scale(model, GROUND);
      glUniformMatrix4fv(shader.location("Model"), 1, GL_FALSE, glm::value_ptr(model));
      glUniform3f(shader.location("COLOR"), 0.5f, 0.4f, 0.1f);
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
      
      glfwSwapBuffers(window);
      glfwPollEvents();
   }
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);
   glfwDestroyWindow(window);
   glfwTerminate();
   return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}

void InputProcess(GLFWwindow* window)
{
   const float speed = 0.05f;
   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
   else
   { 
      if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
         PLAYER += DIRECTION_VECTOR * speed;
      if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
         PLAYER -= DIRECTION_VECTOR * speed;
      if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
         PLAYER -= glm::normalize(glm::cross(DIRECTION_VECTOR, UP_VECTOR)) * speed;
      if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
         PLAYER += glm::normalize(glm::cross(DIRECTION_VECTOR, UP_VECTOR)) * speed;
      if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && PLAYER.y <=2.2f)
         PLAYER.y += UP_VECTOR.y * speed * 2.2f;
   }
}
