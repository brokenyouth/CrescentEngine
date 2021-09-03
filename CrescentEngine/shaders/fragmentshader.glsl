#version 450

out vec4 fragColor;

in vec2 TexCoord;

uniform sampler2D diffuse0;


void main()
{
    fragColor = texture(diffuse0, TexCoord);
}