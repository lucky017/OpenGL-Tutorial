

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 TextureAttribute1;
layout (location = 3) in vec2 TextureAttribute2;

out vec3 ourColor;
out vec2 TextureCoordinate1;
out vec2 TextureCoordinate2;
void main()
{
    gl_Position = vec4(aPos, 1.0f);
    ourColor = aColor;
    TextureCoordinate1 = TextureAttribute1;
    TextureCoordinate2 = TextureAttribute2;
}
