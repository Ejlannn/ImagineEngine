#version 330

in vec2 position;

out vec3 colorO;

uniform vec3 color;

void main(void)
{
	colorO = color;
	gl_Position = vec4(position, 0.0, 1.0);
}