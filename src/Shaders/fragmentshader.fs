

//Fragment Shader source code

#version 330 core
out vec4 FragColor;

uniform vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    FragColor = vec4(ourColor, 1.0f); 
}
