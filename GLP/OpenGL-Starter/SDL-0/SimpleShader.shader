#version 330 core
in vec3 pos;
in vec3 color;
out vec3 ourColor;
uniform vec2 ourMovement;
uniform float ourScale;

void main()
{
    //gl_Position = vec4(pos + ourMovement, 1.0);
    gl_Position = vec4((pos.x + ourMovement.x)*ourScale , (pos.y+ ourMovement.y)*ourScale , pos.z*ourScale, 1.0);

    ourColor = color;
}