#version 330

in vec3 colorO;

out vec4 out_Color;

void main(void)
{
	out_Color = vec4(colorO,0.6);
}