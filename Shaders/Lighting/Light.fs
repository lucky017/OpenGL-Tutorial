
#version 330 core

out vec4 FragColor;

uniform vec3 LightCubeColor;
uniform vec3 LightSourceColor;

void main()
{
    FragColor = vec4(LightCubeColor * LightSourceColor, 1.0f);
}

