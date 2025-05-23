
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 object;
uniform mat4 movement;
uniform mat4 rotation;

void main()
{
    gl_Position = object * movement * vec4(aPos, 1.0f);
    ourColor = aColor;
}
