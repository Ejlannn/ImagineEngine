#version 400 core

in vec2 position;
in vec2 textureVector;

out vec2 textureCoords;

uniform mat4 projectionMatrix;

void main(void)
{
	textureCoords = textureVector;
	gl_Position = vec4(position, 0.0, 1.0);
}