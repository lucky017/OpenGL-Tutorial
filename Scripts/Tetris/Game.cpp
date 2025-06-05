
#include "../../Include/shaders.h"
#include<GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glm/matrix.hpp>

#define WIDTH 800.0f
#define HEIGHT 600.0f


struct Tetris{
     Tetris() {}

     private:
     inline void L_Shape(const GLint &Location);
     inline void _7_Shape(const GLint &Location);
     inline void middlefinger_Shape(const GLint &Location);
     inline void Z_Shape(const GLint &Location);
     inline void invertedZ_Shape(const GLint &Location);
     inline void cube_shape(const GLint &Location);
     inline void straight_Shape(const GLint &Location);

     public: 
     inline void RandomShape(const GLint &Location);
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void InputAction(GLFWwindow* window);

const float EndPoint = -1.0f;

int main()
{
     glfwInit();
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
     
     GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Tetris", NULL, NULL);
     if(!window){
          std::cout << "Error Creating Opengl Window.\n";
          glfwTerminate();
          return 0;
     }
     glfwMakeContextCurrent(window);
     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

     gladLoadGL();

     float pixel[6 * 3] = {
          -0.2f, - 0.2f, 0.0f, // A
           0.025f, 0.2f, 0.0f, // B
          -0.2f,   0.2f, 0.0f, // C

          -0.2f,  -0.2f, 0.0f, // A
           0.025f, 0.2f, 0.0f, // C
           0.025f,-0.2f, 0.0f  // D
     };
     Shader shader("Tetris/Game.vs", "Tetris/Game.fs");

     GLuint VAO, VBO;
     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);
     
     glBindVertexArray(VAO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(pixel), pixel, GL_STATIC_DRAW);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);

     shader.use();
     Tetris tetris;
     while(!glfwWindowShouldClose(window))
     {
          InputAction(window);
          //glEnable(GL_COLOR_BUFFER_BIT);
          
          glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT);
          GLint Location = shader.location("model");
          
          tetris.RandomShape(Location);
          glfwSwapBuffers(window);
          glfwPollEvents();
     }
     shader.DeleteProgram();
     glDeleteBuffers(1, &VBO);
     glDeleteVertexArrays(1, &VAO);
     glfwDestroyWindow(window);
     glfwTerminate();
     return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
     glViewport(0, 0, width, height);
}

void InputAction(GLFWwindow* window)
{
     if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
          glfwSetWindowShouldClose(window, true);
     }
}
inline void Tetris::RandomShape(const GLint &Location)
{
    _7_Shape(Location);
}

inline void Tetris::straight_Shape(const GLint &Location)
{
    glm::mat4 Block[4];
     float move = 0.0f;
     for(int i = 0; i<4; i++){
          Block[i] = glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.0));
          move += 0.41f;
          Block[i] = glm::translate(Block[i], glm::vec3(0.0f, move, 0.0f));
          glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Block[i]));
          glDrawArrays(GL_TRIANGLES, 0, 24);
     }
}
inline void Tetris::L_Shape(const GLint &Location)
{
    glm::mat4 Block[4];
    float move = 0.0f;
    for(int i=0; i<4; i++){
        Block[i] = glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.0));
        move += 0.41f;
        if(i<3){
            Block[i] = glm::translate(Block[i], glm::vec3(0.0f, move, 0.0f));
        } else{
            Block[i] = glm::translate(Block[i], glm::vec3(0.232, 0.41, 0.0f));
        }
        glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Block[i]));
        glDrawArrays(GL_TRIANGLES, 0, 24);
    }
}
inline void Tetris::_7_Shape(const GLint &Location)
{
    glm::mat4 Block[4];
    float move = 0.0f;
    for(int i=0; i<4; i++){
        Block[i] = glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.0));
        if(i<3){
            move += 0.41f;
            Block[i] = glm::translate(Block[i], glm::vec3(0.0f, move, 0.0f));
        } else{
            Block[i] = glm::translate(Block[i], glm::vec3(0.232, move, 0.0f));
        }
        glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Block[i]));
        glDrawArrays(GL_TRIANGLES, 0, 24);
    }
}
