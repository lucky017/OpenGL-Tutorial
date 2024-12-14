
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 Texture1;
//layout (location = 3) in vec2 Texture2;

out vec3 ourColor;
out vec2 Tex1;
//out vec2 Tex2;

uniform mat4 transform;

void main()
{
    gl_Position =  transform * vec4(aPos, 1.0f);
    ourColor = aColor;
    Tex1 = Texture1;
  //  Tex2 = Texture2;
}
