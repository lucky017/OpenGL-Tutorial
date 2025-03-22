

#include "../../Include/shaders.h"
#include<GLFW/glfw3.h>
#include<cmath>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#define WIDTH 800
#define HEIGHT 800

const char* vertexshadersource = " #version 330 core\n"
                                 " layout (location = 0) in vec3 aPos; \n"
                                 " layout (location = 1) in vec3 aColor; \n"
                                 " out vec3 ourColor; \n"
                                 " uniform mat4 transform;"
                                 " void main() \n"
                                 " { \n"
                                 " gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                 " ourColor = aColor; \n"
                                 " }\0";
const char* fragmentshadersource=" #version 330 core\n"
                                 " out vec4 FragColor;\n"
                                 " uniform vec4 Colors; \n"
                                 " in vec3 ourColor; \n"
                                 " void main() \n"
                                 " { \n"
                                 " FragColor = vec4(ourColor, 1.0f) + Colors;\n"
                                 " }\0";


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
float colors_by_time();

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "CINEMA", NULL, NULL);
  if(!window){
    std::cout << "WINDOW ERROR YOU M.F." << std::endl;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
 
  gladLoadGL();  // important

  Shader shader(vertexshadersource, fragmentshadersource);

  GLfloat vertices[] = {
//            Vertices                     Colors
         0.00f,  0.50f, 0.0f,/*A0*/   0.5f, 0.0f, 0.0f,
        -0.50f,  0.25f, 0.0f,/*B1*/   0.0f, 0.5f, 0.0f,
        -0.25f, -0.50f, 0.0f,/*C2*/   0.0f, 0.0f, 0.5f,
         0.25f, -0.50f, 0.0f,/*D3*/   0.2f, 0.0f, 0.0f,
         0.50f,  0.25f, 0.0f,/*E4*/   0.0f, 0.2f, 0.0f,
         0.10f,  0.10f, 0.0f,/*G5*/   0.0f, 0.0f, 0.2f,
         0.00f, -0.25f, 0.0f,/*I6*/   1.0f, 0.0f, 0.0f, 
         0.15f,  0.00f, 0.0f,/*J7*/   0.0f, 1.0f, 0.0f
  };
  GLuint indices[9] = {
      1, 5, 3,//BFD
      0, 7, 2,//AJC
      1, 6, 4//BIE
   };

  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  shader.use();
  while(!glfwWindowShouldClose(window))
  {
    glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float values = colors_by_time();
    shader.setFloat("Colors", values, values, values, 1.0f);

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
    trans = glm::rotate(trans, (GLfloat)glfwGetTime()* glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    GLfloat Location = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(trans));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(trans));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  
    
    glfwSwapBuffers(window);
    glfwPollEvents();

  }

  shader.DeleteProgram(); 
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glfwDestroyWindow(window);
  glfwTerminate();
}


float colors_by_time()
{
  float timeValue = glfwGetTime();
    return sin(timeValue) / 2.0f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}
