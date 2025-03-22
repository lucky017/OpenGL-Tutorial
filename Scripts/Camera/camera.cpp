  
#include "../../Include/shaders.h"
#include<GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../../Include/stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define WIDTH 1380.0f
#define HEIGHT 780.0f

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void InputProcess(GLFWwindow* window);

glm::vec3 CAM_POSITION(0.0f, 0.0f, 3.0f);
glm::vec3 DIR_VECTOR(0.0f, 0.0f, -1.0f); 
glm::vec3 UP_VECTOR(0.0f, 1.0f, 0.0f);

int main()
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "CAMERA", NULL, NULL);
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   if(window == NULL){
      std::cout << "ERROR CREATING OPENGL WINDOW" << std::endl;
      glfwTerminate();
      return -1;
   }

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
   GLuint VAO, VBO; // VERTEX_ARRAY_OBJECT && VERTEX_BUFFER_OBJECT
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   
    shader.use();
    
    glEnable(GL_DEPTH_TEST);
    
    while(!glfwWindowShouldClose(window))
    {
      // Exit when pressed "ESC"
        InputProcess(window);
         
        GLfloat WindowColor = sin(glfwGetTime())/1.0f;
        if(WindowColor <=0.09f)
          WindowColor = 0.1f;
        else if(WindowColor >= 0.91f) 
          WindowColor = 0.90f;
        glClearColor(WindowColor * 0.8f, WindowColor * 0.2f, WindowColor * 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // shader.use();
        glm::mat4 ModelMatrix = glm::mat4(1.0f);
        glm::mat4 ViewMatrix = glm::mat4(1.0f);
        glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
        //const float radius = 6.0f;
        //float CAM_X = sin(glfwGetTime()) * radius;
        //float CAM_Z = cos(glfwGetTime()) * radius;
        //View = glm::translate(View, glm::vec3(0.0f, 0.0f, -3.0f));
        
        ProjectionMatrix = glm::perspective(glm::radians(60.0f), WIDTH/HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(shader.location("Projection"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

        for(int i=0; i<6; i++)
        {
            ModelMatrix = glm::translate(ModelMatrix, CubePosition[i]);
            //ModelMatrix = glm::rotate(ModelMatrix, (float)glfwGetTime() * glm::radians(90.0f), glm::vec3(0.5, 1.0, 0.0));
            glUniformMatrix4fv(shader.location("Model"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
            ViewMatrix = glm::lookAt(CAM_POSITION, DIR_VECTOR, UP_VECTOR);

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
  const GLfloat CamSpeed = 0.06f;
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    CAM_POSITION += CamSpeed * DIR_VECTOR;
  else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    CAM_POSITION -= CamSpeed * DIR_VECTOR;
  else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    CAM_POSITION -= glm::normalize(glm::cross(DIR_VECTOR, UP_VECTOR)) * CamSpeed;
  else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    CAM_POSITION += glm::normalize(glm::cross(DIR_VECTOR, UP_VECTOR)) * CamSpeed;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

