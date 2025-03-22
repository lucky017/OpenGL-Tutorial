
#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 Texture;

uniform sampler2D uniform_Texture;

void main()
{
    FragColor = texture(uniform_Texture, Texture) * vec4(0.5f, 0.5f, 0.5f, 1.0f);
}

