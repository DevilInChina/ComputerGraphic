#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
out vec3 ourcolor;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
//modelViewMatrix
void main()
{
    gl_Position =projectionMatrix *modelViewMatrix * vec4(position.x, position.y, position.z, 1.0);
    ourcolor = color;
}