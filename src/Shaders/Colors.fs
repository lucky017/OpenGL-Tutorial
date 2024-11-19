
#version 330 core

in vec3 ourColor;
uniform vec4 Colors;
out vec4 FragColor;

void main()
{
    FragColor = vec4(ourColor, 1.0f) * Colors;
}
