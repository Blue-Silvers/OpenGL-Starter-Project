#version 330 core
out vec4 FragColor;
out vec3 color;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0f);
    //color = ourColor;
}
