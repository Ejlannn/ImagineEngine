#version 330

in vec4 color;
in vec2 textureCoords;
flat in float visibility;
in vec4 lightToAdd[4];

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
		out_Color = color;
	}
	
	out_Color = mix(vec4(bgColor,1.0),out_Color,visibility);
	
	vec3 convAmbientColor = vec3(1.0,1.0,1.0) - ambientColor;
	
	out_Color = out_Color - vec4(convAmbientColor,0.0);
	
	for(int i=0;i<4;i++)
	{
		vec4 lightToAddFinal = lightToAdd[i] - vec4(ambientColor, 0.0);
		
		lightToAddFinal.x = clamp(lightToAddFinal.x,0.0,0.9);
		lightToAddFinal.y = clamp(lightToAddFinal.y,0.0,0.9);
		lightToAddFinal.z = clamp(lightToAddFinal.z,0.0,0.9);
		lightToAddFinal.w = 0.0;
		
		out_Color = out_Color + lightToAddFinal;
	}
	
	out_Color.w = clamp(out_Color.w,0.0,1.0);
}