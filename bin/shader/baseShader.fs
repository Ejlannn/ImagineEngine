#version 400 core

in vec3 color;
in vec2 textureCoords;
in float visibility;

out vec4 out_Color;

uniform bool textured;

uniform sampler2D sampler;

uniform vec3 bgColor;
uniform vec3 ambientColor;

void main(void)
{
	if(textured == true)
	{
		out_Color = texture2D(sampler,textureCoords);
	}
	else
	{
		out_Color = vec4(color,1.0);
	}
	
	out_Color = mix(vec4(bgColor,1.0),out_Color,visibility);
	
	vec3 convAmbientColor = vec3(1.0,1.0,1.0) - ambientColor;
	
	out_Color = out_Color - vec4(convAmbientColor,1.0);
}