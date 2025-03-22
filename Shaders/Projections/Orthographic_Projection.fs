
#version 330 core

out vec4 FragColor;

in vec2 Texture;
uniform sampler2D uniform_Texture;

void main()
{
    FragColor = texture(uniform_Texture, Texture);
}

