#version 330

in vec3 position;
in vec2 textureVector;
in vec3 normalVector;

out vec4 color;
out vec2 textureCoords;
flat out float visibility;
out vec4 lightToAdd[4];

uniform vec4 mainColor;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform float tilingX;
uniform float tilingY;

uniform float density = 0.01;
uniform float gradient = 1.5;

uniform int lightType[4];
uniform float lightRange[4];
uniform vec3 lightPosition[4];
uniform vec3 lightColor[4];
uniform float lightIntensity[4];
uniform vec3 lightDir[4];
uniform float lightSpotAngle[4];

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
	
	vec3 surfaceNormal = (transformationMatrix * vec4(normalVector,0.0)).xyz;
	vec3 unitSurfaceNormal = normalize(surfaceNormal);
	
	for(int i=0;i<4;i++)
	{	
		if(lightType[i] == 1)
		{
			float lightIntensMain = clamp(lightIntensity[i],0.0,10.0) / 10;
			float lightIntensMainInv = (10.0 - lightIntensMain) / 10;
				
			vec3 unitLightDir = normalize(lightDir[i]);
				
			float lightDotProduct = dot(unitSurfaceNormal,unitLightDir);
			lightDotProduct = (lightDotProduct,0.0);
			float lightDotProductInv = (1.0 - lightDotProduct) / 10;
			
			lightToAdd[i] = vec4(lightColor[i].x - lightDotProductInv + lightIntensMain - 0.5, lightColor[i].y - lightDotProductInv + lightIntensMain - 0.5, lightColor[i].z - lightDotProductInv + lightIntensMain - 0.5, 0.0);
		}
		else if(lightType[i] == 2)
		{
			float distanceToLight = distance(worldPosition.xyz,lightPosition[i]);
			
			if(distanceToLight <= lightRange[i])
			{
				vec3 toLightVector = lightPosition[i] - worldPosition.xyz;
				vec3 unitToLightVector = normalize(toLightVector);
				
				float distanceToLightInv = lightRange[i] - distanceToLight;
				
				float intensityPerc = (distanceToLightInv/lightRange[i]);
				float intensityPercInv = 1.0 - intensityPerc;
				
				float lightIntensMain = clamp(lightIntensity[i],0.0,10.0) / 10;
				float lightIntensMainInv = (10.0 - lightIntensMain) / 10;
				
				float lightDotProduct = dot(unitSurfaceNormal,unitToLightVector);
				lightDotProduct = (lightDotProduct,0.0);
				float lightDotProductInv = (1.0 - lightDotProduct) / 10;
				
				float toSubst = intensityPercInv + lightDotProductInv;
			
				lightToAdd[i] = vec4(lightColor[i].x - toSubst + lightIntensMain - 0.5, lightColor[i].y - toSubst + lightIntensMain - 0.5, lightColor[i].z - toSubst + lightIntensMain - 0.5, 0.0);
			}
			else
			{
				lightToAdd[i] = vec4(0.0,0.0,0.0,0.0);
			}
		}
		else if(lightType[i] == 3)
		{
			float distanceToLight = distance(worldPosition.xyz,lightPosition[i]);
			
			if(distanceToLight <= lightRange[i])
			{	
				float distanceToLightInv = lightRange[i] - distanceToLight;
				
				float intensityPerc = (distanceToLightInv/lightRange[i]);
				float intensityPercInv = 1.0 - intensityPerc;
				
				float lightIntensMain = clamp(lightIntensity[i],0.0,10.0) / 10;
				float lightIntensMainInv = (10.0 - lightIntensMain) / 10;
				
				vec3 unitLightDir = normalize(lightDir[i]);
				
				float lightDotProduct = dot(unitSurfaceNormal,unitLightDir);
				lightDotProduct = (lightDotProduct,0.0);
				float lightDotProductInv = (1.0 - lightDotProduct) / 10;
				
				float toSubst = intensityPercInv + lightDotProductInv;
			
				lightToAdd[i] = vec4(lightColor[i].x - toSubst + lightIntensMain - 0.5, lightColor[i].y - toSubst + lightIntensMain - 0.5, lightColor[i].z - toSubst + lightIntensMain - 0.5, 0.0);
			}
			else
			{
				lightToAdd[i] = vec4(0.0,0.0,0.0,0.0);
			}
		}
		else if(lightType[i] == 0)
		{
			lightToAdd[i] = vec4(0.0,0.0,0.0,0.0);
		}
		
		lightToAdd[i].x = clamp(lightToAdd[i].x,0.0,0.9);
		lightToAdd[i].y = clamp(lightToAdd[i].y,0.0,0.9);
		lightToAdd[i].z = clamp(lightToAdd[i].z,0.0,0.9);
	}
	
	gl_Position = projectionMatrix * positionRelativeToCam;
}