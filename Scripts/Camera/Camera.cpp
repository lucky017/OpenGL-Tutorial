  
#include "../../Include/shaders.h"
#include<GLFW/glfw3.h>
#include <glm/trigonometric.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "../../Include/stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define WIDTH 1380.0f
#define HEIGHT 780.0f

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursorPos_callback(GLFWwindow* window, double x_cursorPos, double y_cursorPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void InputProcess(GLFWwindow* window);

glm::vec3 cameraPosition(0.0f, 0.0f, 3.0f);
glm::vec3 directionVector(0.0f, 0.0f, -1.0f); 
glm::vec3 upVector(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float x_lastcursorPos = WIDTH/2;
float y_lastcursorPos = HEIGHT/2;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 60.0f;
bool firstMouseCallback = true;

int main()
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "CAMERA", NULL, NULL);
   if(window == NULL){
      std::cout << "ERROR CREATING OPENGL WINDOW" << std::endl;
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   glfwSetCursorPosCallback(window, cursorPos_callback);
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   glfwSetScrollCallback(window, scroll_callback);
   gladLoadGL();
   
  const GLfloat vertices[] = {
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
  const glm::vec3 CubePosition[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 1.0f,  1.0f, -1.0f), 
    glm::vec3( 1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -2.3f),  
    glm::vec3(-2.4f,  0.4f, -3.5f),
    glm::vec3( 3.0f, -1.5f, -1.2f),
    glm::vec3( 1.9f,  2.0f, -3.0f),
    glm::vec3(-3.0f,  2.0f, -2.0f),
    glm::vec3(-1.2f,  0.0f, -3.0f)
  };
  const glm::vec3 CubeColors[] = {
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.5f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.5f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.5f)

  };

  Shader shader("Camera/camera.vs", "Camera/camera.fs");
  GLuint VAO, VBO; 
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
   
    shader.use();  
    glEnable(GL_DEPTH_TEST);
    std::cout << "{ " << directionVector.x << ", "
                      << directionVector.y << ", "
                      << directionVector.z << " }"<< std::endl;
  while(!glfwWindowShouldClose(window))
  {
    float CurrentFrame = glfwGetTime();
    deltaTime = CurrentFrame - lastFrame;
    lastFrame = CurrentFrame;

    InputProcess(window);
         
    GLfloat WindowColor = sin(glfwGetTime())/1.0f;
    if(WindowColor <=0.09f)
      WindowColor = 0.1f;
    else if(WindowColor >= 0.91f) 
      WindowColor = 0.90f;
    glClearColor(WindowColor * 0.3f, WindowColor * 0.2f, WindowColor * 0.2f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    glm::mat4 ModelMatrix = glm::mat4(1.0f);
    glm::mat4 ViewMatrix = glm::mat4(1.0f);
    glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
        //const float radius = 6.0f;
        //float CAM_X = sin(glfwGetTime()) * radius;
        //float CAM_Z = cos(glfwGetTime()) * radius;
        //View = glm::translate(View, glm::vec3(0.0f, 0.0f, -3.0f));
        
    ProjectionMatrix = glm::perspective(glm::radians(fov), WIDTH/HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(shader.location("Projection"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

    for(int i=0; i<6; i++)
    {
        ModelMatrix = glm::translate(ModelMatrix, CubePosition[i]);
        glUniformMatrix4fv(shader.location("Model"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
        ViewMatrix = glm::lookAt(cameraPosition, cameraPosition + directionVector, upVector);
        glUniformMatrix4fv(shader.location("View"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
        glm::vec3 aColor = CubeColors[i];
        glUniform4f(glGetUniformLocation(shader.ID, "color"), aColor.r, aColor.g, aColor.b, 1.0f);
            //shader.setFloat("fragment", 0.0f, 0.0f, 0.0f, 0.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36); 
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void InputProcess(GLFWwindow* window)
{
  const GLfloat CamSpeed = 2.0f *  deltaTime;
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cameraPosition += CamSpeed * directionVector;
  else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cameraPosition -= CamSpeed * directionVector;
  else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cameraPosition -= glm::normalize(glm::cross(directionVector, upVector)) * CamSpeed;
  else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cameraPosition += glm::normalize(glm::cross(directionVector, upVector)) * CamSpeed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void cursorPos_callback(GLFWwindow* window, double x_cursorPos, double y_cursorPos)
{
  if(firstMouseCallback)
  {
    x_lastcursorPos = (float)x_cursorPos;
    y_lastcursorPos = (float)y_cursorPos;
    firstMouseCallback = false;
  }
  float xoffset = (float)x_cursorPos - x_lastcursorPos;
  float yoffset = y_lastcursorPos - (float)y_cursorPos;
  x_lastcursorPos = (float)x_cursorPos;
  y_lastcursorPos = (float)y_cursorPos;

  float sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  if(pitch > 89.0f)
    pitch = 89.0f;
  if(pitch < -89.0f)
    pitch = -89.0f;

  if (yaw > 360.0f) yaw -= 360.0f;
  if (yaw < 0.0f) yaw += 360.0f;

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    std::cout << "{ " << directionVector.x << ", "
                      << directionVector.y << ", "
                      << directionVector.z << " }"<< std::endl;
  directionVector = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  fov -= (float)yoffset;

  if(fov < 1.0f)
    fov = 1.0f;
  if(fov > 60.0f)
    fov = 60.0f;
}
