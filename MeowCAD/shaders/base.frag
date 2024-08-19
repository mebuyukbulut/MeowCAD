#version 460 core

in vec3 bColor;
in vec2 bTexCoord;

out vec4 FragColor;  

uniform sampler2D ourTexture;

void main(){
   FragColor = texture(ourTexture, bTexCoord);
}