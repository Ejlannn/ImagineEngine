#version 400 core

in vec3 position;
in vec2 textureVector;
in vec3 normalVector;

out vec3 color;
out vec2 textureCoords;
out float visibility;
out vec3 lightToAdd;

uniform vec3 mainColor;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform float tilingX;
uniform float tilingY;

uniform float density = 0.01;
uniform float gradient = 1.5;

uniform int lightType[4];
uniform vec3 lightColor[4];
uniform float lightIntensity[4];
uniform vec3 lightPosition[4];
uniform float lightRange[4];

void main(void)
{
	color = mainColor;
	textureCoords = textureVector;
	textureCoords.x = textureCoords.x * tilingX;
	textureCoords.y = textureCoords.y * tilingY;

	vec4 worldPosition = transformationMatrix * vec4(position,1.0);
	
	vec4 positionRelativeToCam = viewMatrix * worldPosition;
	
	float distance1 = length(positionRelativeToCam.xyz);
	
	visibility = exp(-pow((distance1 * density), gradient));
	visibility = clamp(visibility,0.0,1.0);
	
	lightToAdd = vec3(0.0,0.0,0.0);
	
	for(int i=0;i<4;i++)
	{
		if(lightType[i] == 1)
		{
		}
		
		if(lightType[i] == 2)
		{
			float distanceToLight = distance(worldPosition.xyz,lightPosition[i]);
			
			if(distanceToLight <= lightRange[i])
			{
				float tempRang = lightRange[i] - distanceToLight;
				
				float toAdd1 = tempRang / 10.0;
				
				vec3 toAdd = vec3(lightColor[i].x + toAdd1 * lightIntensity[i] - 0.8, lightColor[i].y + toAdd1 * lightIntensity[i] - 0.8, lightColor[i].z + toAdd1 * lightIntensity[i] - 0.8);
				
				float tX = clamp(toAdd.x,0.0,lightColor[i].x);
				float tY = clamp(toAdd.y,0.0,lightColor[i].y);
				float tZ = clamp(toAdd.z,0.0,lightColor[i].z);
				
				vec3 toAddFinal = vec3(tX, tY, tZ);
				
				lightToAdd = lightToAdd + toAddFinal;
			}
		}
		
		if(lightType[i] == 3)
		{
		}
	}
	
	lightToAdd.x = clamp(lightToAdd.x,0.0,0.9);
	lightToAdd.y = clamp(lightToAdd.y,0.0,0.9);
	lightToAdd.z = clamp(lightToAdd.z,0.0,0.9);
	
	gl_Position = projectionMatrix * positionRelativeToCam;
}