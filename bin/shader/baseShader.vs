#version 400 core

in vec3 position;
in vec2 textureVector;
in vec3 normalVector;

out vec3 color;
out vec2 textureCoords;
out float visibility;

uniform vec3 mainColor;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform float tilingX;
uniform float tilingY;

uniform float density = 0.01;
uniform float gradient = 1.5;

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
	
	gl_Position = projectionMatrix * positionRelativeToCam;
}