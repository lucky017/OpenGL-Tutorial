
#!/bin/bash


g++ -o exe/opengl src/"$1" src/headers/shadersbysource.cpp glad/src/glad.c -lglfw -lGL -ldl

