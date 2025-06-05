
#include "../../Include/shaders.h"
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#define WIDTH 1380.0f
#define HEIGHT 720.0f

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void InputAction(GLFWwindow* window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LIGHT", NULL, NULL);
    if(!window){
        std::cout << "Seem to be a problem with window creation\n"
                << "Check for any any bugs in the codebase\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    gladLoadGL();

   const GLfloat cube_vertices[8 * 3] = {
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

    Shader shader("Lighting/Light.vs", "Lighting/Light.fs");
    
    GLuint VAO, VBO, EBO, LightVAO;
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &LightVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindVertexArray(LightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shader.use();
    glEnable(GL_DEPTH_TEST);
    std::cout << "Error Detected" << std::endl;
    GLint Location = 0;
    while(!glfwWindowShouldClose(window))
    {
        InputAction(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Location = shader.location("model");
        glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        float offset = glfwGetTime();
        model = glm::rotate(model, offset * glm::radians(40.0f), glm::vec3(0.8f, 0.2f, -0.3f));
        glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(model));
        Location = shader.location("view");
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(view));
        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), WIDTH/HEIGHT, 0.1f, 100.0f);
        Location = shader.location("Projection");
        glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Projection));
        
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader.DeleteProgram();
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void InputAction(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
}

