#version 330 core
out vec4 FragColor;

uniform vec3 IDcolor;

void main(){
    FragColor = vec4(IDcolor, 1.0);
} 