
#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 Tex;

uniform sampler2D Texture;

void main()
{
    FragColor = texture(Texture, Tex);   
}

