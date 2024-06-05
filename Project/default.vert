#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 matrix;
uniform mat4 projection;


out vec3 Normal;

void main()
{
    Normal = aNormal;
    gl_Position = projection * matrix * vec4(aPos, 1.0);
}



