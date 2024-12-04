#version 430 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;
in mat4 View;

uniform float modeFlag;
layout(binding = 7) uniform sampler2D matcapTexture;

void main()
{
    if(modeFlag > 0.5){    
        FragColor = vec4(1,165./255.,0, 0.3);
        return;
    }  
    // Move normal to view space
    highp vec2 muv = vec2(View * vec4(normalize(Normal), 0))*0.5+vec2(0.5,0.5);
    // read texture inverting Y value
    FragColor = texture2D(matcapTexture, vec2(muv.x, 1.0-muv.y));


    
}