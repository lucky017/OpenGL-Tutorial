

#include "headers/shaders.h"
#include<GLFW/glfw3.h>
#include<cmath>

const char* vertexshadersource = " #version 330 core\n"
                                 " layout (location = 0) in vec3 aPos; \n"
                                 " layout (location = 1) in vec3 aColor; \n"
                                 " out vec3 ourColor; \n"
                                 " void main() \n"
                                 " { \n"
                                 " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
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

unsigned int WIDTH  = 800;
unsigned int HEIGHT = 800;

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
//            Textures               Colors
          -1.0f, -1.0f, 0.0f,   0.5f, 0.0f, 0.0f,
          -1.0f,  1.0f, 0.0f,   0.0f, 0.5f, 0.0f,
           1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 0.5f,
           1.0f,  1.0f, 0.0f
  };
   GLuint indices[6] = {
      0, 1, 2,
      1, 2, 3
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

//------------------------------------------------

float colors_by_time()
{
  float timeValue = glfwGetTime();
    return sin(timeValue) / 2.0f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}
