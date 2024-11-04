#version 330 core
in vec3 pos;
in vec3 color;
out vec3 ourColor;
uniform vec4 ourMovement;

void main()
{
    gl_Position = vec4(pos, 1.0);
    //gl_Position = ourMovement;
    ourColor = color;
}