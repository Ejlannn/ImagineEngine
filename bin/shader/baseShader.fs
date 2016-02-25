#version 400 core

in vec3 color;
in vec2 textureCoords;
in float visibility;
in vec3 finalLightToAdd[4];

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
	
	vec4 addToOutColor = vec4(0.0,0.0,0.0,1.0);
	
	addToOutColor = addToOutColor + vec4(finalLightToAdd[0],0.0);
	addToOutColor = addToOutColor + vec4(finalLightToAdd[1],0.0);
	addToOutColor = addToOutColor + vec4(finalLightToAdd[2],0.0);
	addToOutColor = addToOutColor + vec4(finalLightToAdd[3],0.0);
	
	addToOutColor.x = clamp(addToOutColor.x,0.0,0.9);
	addToOutColor.y = clamp(addToOutColor.y,0.0,0.9);
	addToOutColor.z = clamp(addToOutColor.z,0.0,0.9);
	
	out_Color = out_Color + addToOutColor;
	
	out_Color.w = 1.0;
}