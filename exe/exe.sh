
#!/bin/bash

g++ -o exe/opengl src/"$1" src/Implementations/$2 glad/src/glad.c -lglfw -lGL -ldl

#g++ -o exe/opengl src/"$1" glad/src/glad.c -lglfw -lGL -ldl
