#version 330 core
in vec3 pos;
in vec3 color;
out vec3 ourColor;
uniform float ourMovement;
uniform float ourScale;
uniform float speedTest;

void main()
{
    //gl_Position = vec4(pos + ourMovement, 1.0);
    gl_Position = vec4((pos.x + ourMovement)*ourScale , pos.y*ourScale + speedTest, pos.z*ourScale, 1.0);

    ourColor = color;
}