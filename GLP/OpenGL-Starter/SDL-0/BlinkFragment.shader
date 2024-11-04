#version 330 core
out vec4 FragColor;
uniform vec4 ourShift;

void main()
{
    FragColor = ourShift;
}
