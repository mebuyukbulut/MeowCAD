#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){   

    mat4 MVP= projection * view * model ;
    vec4 myPos = vec4(aPos, 1.0);
    vec4 pos = MVP * myPos;
    gl_Position = pos;
}