#version 330

in vec2 position;
in vec2 textureVector;

out vec2 textureCoords;

uniform mat4 projectionMatrix;

void main(void)
{
	textureCoords = textureVector;
	gl_Position = projectionMatrix * vec4(position, 0.0, 1.0);
}