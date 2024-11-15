

#include <glad/glad.h> // Include GLAD
#include <GLFW/glfw3.h>
#include <iostream>
#include "h_files/source.h"
#define STB_IMAGE_IMPLEMENTATION
#include "h_files/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
 
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "OPENGL", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  if(window == NULL)
  {
    std::cout << "[Error]: Error Creating a window!!" << std::endl;
  }
  
  gladLoadGL();

  glViewport(0, 0, 800, 800);

  Shader shader1(1, "/home/lucky/opengl/src/shaders/vertexshader.vs", "/home/lucky/opengl/src/shaders/fragmentshader_1.fs");
  Shader shader2(2, "/home/lucky/opengl/src/shaders/vertexshader.vs", "/home/lucky/opengl/src/shaders/fragmentshader_2.fs");
  
  GLfloat vertices[] = {
    //      vertices            colors            Textures
      -1.0f, -1.0f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
       1.0f, -1.0f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
      -1.0f,  1.0f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f
  };
  GLfloat t_vertices[] = {
    //      vertices            colors            Textures
      -1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,
       1.0f,  1.0f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,  
       1.0f, -1.0f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f
  };
  GLuint indices[] = {
    0, 1, 2 
  };

  GLuint VBO[2], VAO[2], EBO[2];
  glGenVertexArrays(2, &VAO[0]);
  glGenBuffers(2, &VBO[0]);
  glGenBuffers(2, &EBO[0]);

  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(3* sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  GLuint texture1, texture2;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  const char* Path = "/home/lucky/opengl/src/textures/wall.jpg";
  unsigned char* data = stbi_load(Path, &width, &height, &nrChannels, 0);

  if(data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else{
    std::cout << "{ ERROR } :: FUCK!! TEXTURE HAS NOT LOADED! " << std::endl;
  }
  stbi_image_free(data);
//-------------------------------------------------------------------------------
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  //Path = "/home/lucky/opengl/src/source/container.jpg";
  data = stbi_load("/home/lucky/.config/hyde/themes/Decay Green/wallpapers/Maul-Anakin.png", &width, &height, &nrChannels, STBI_rgb_alpha);

  if(data){
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
  } else {
      std::cout << " FUCK I MESSED UP AGAIN WITH TEXTURE 2!!" << std::endl;
  }
  stbi_image_free(data);
//---------------------------------------------------------------
//----------------------------------------------------------------
  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

  glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertices), t_vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  GLuint texture3, texture4;
  glGenTextures(1, &texture3);
  glBindTexture(GL_TEXTURE_2D, texture3);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  Path = "/home/lucky/opengl/src/textures/container.jpg";
  unsigned char* Data1 = stbi_load(Path, &width, &height, &nrChannels, 0);
  stbi_set_flip_vertically_on_load(true);
  if(Data1){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data1);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else{
    std::cout << "{ ERROR } :: FUCK!! TEXTURE HAS NOT LOADED! " << std::endl;
  }
  stbi_image_free(Data1);
//------------------------------------------------------------------------------------
  glGenTextures(1, &texture4);
  glBindTexture(GL_TEXTURE_2D, texture4);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  stbi_set_flip_vertically_on_load(true);
  Path = "/home/lucky/.config/hyde/themes/Decay Green/wallpapers/Maul-Anakin.png";
  Data1 = stbi_load(Path, &width, &height, &nrChannels, STBI_rgb_alpha);
  if(Data1){
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data1);
      glGenerateMipmap(GL_TEXTURE_2D);
  } else {
      std::cout << " FUCK I MESSED UP AGAIN WITH TEXTURE 2!!" << std::endl;
  }

    shader1.use();
    shader1.setInt("ourTexture1", 0);
    shader1.setInt("ourTexture2", 1);

    shader2.use();
    shader2.setInt("ourTexture1", 0);
    shader2.setInt("ourTexture2", 1);
 
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  //----------LOOP-FOR-PRINTING-------------------------------
  while(!glfwWindowShouldClose(window))
  {
    processInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


    glClear(GL_COLOR_BUFFER_BIT);
    shader1.use(); 
    //shader1.setFloat("ourColor", 1.0f, 0.0f, 0.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glBindVertexArray(VAO[0]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); 
  
    shader2.use();
    //shader1.setFloat("ourColor", 0.0f, 0.0f, 1.0f); 
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture3);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture4); 
    glBindVertexArray(VAO[1]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glDeleteTextures(1, &texture1);
  glDeleteTextures(1, &texture2);
  glDeleteTextures(1, &texture3);
  glDeleteTextures(1, &texture4);
  glDeleteVertexArrays(2, VAO);
  glDeleteBuffers(2, VBO);
  glDeleteBuffers(2, EBO);
  shader1.DeleteProgram();
  shader2.DeleteProgram();
  glfwDestroyWindow(window);
  glfwTerminate();
}



