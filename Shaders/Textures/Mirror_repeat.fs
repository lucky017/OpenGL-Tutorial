

#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TextureCoordinate1;
in vec2 TextureCoordinate2;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
    FragColor = mix(texture(Texture1, TextureCoordinate1), texture(Texture2, TextureCoordinate2), 0.5);
}
