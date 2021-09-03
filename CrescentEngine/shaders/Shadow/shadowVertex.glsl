#version 450

layout (location = 0) in vec3 _position;
layout (location = 1) in vec3 _normal;
layout (location = 2) in vec3 _color;
layout (location = 3) in vec2 _texCoord;

out vec3 Position;
out vec3 Normal;
out vec3 Color;
out vec2 TexCoord;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
    Position = _position;
	Normal = _normal;
	Color = _color;
	TexCoord = _texCoord;
    gl_Position = projectionMatrix * modelMatrix * vec4(_position, 1.0f);
}