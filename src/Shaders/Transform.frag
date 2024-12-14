
#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 Tex1;
//in vec2 Tex2;

uniform sampler2D Texture1;
//uniform sampler2D Texture2;

void main()
{
    FragColor = texture(Texture1, Tex1);   
}

