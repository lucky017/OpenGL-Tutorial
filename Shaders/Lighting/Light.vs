
#version 330

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 Projection;

void main()
{
    gl_Position = Projection * view * model * vec4(aPos, 1.0f);
}
