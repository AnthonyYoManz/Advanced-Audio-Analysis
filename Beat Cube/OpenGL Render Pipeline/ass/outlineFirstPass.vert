#version 430
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec2 vertTexCoord;
layout(location = 3) in vec4 vertColour;
uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 modelMat;

out vec4 colour;
out vec3 normal;
out vec2 texCoord;

void main()
{
	colour = vertColour;
	normal = normalize((transpose(inverse(viewMat * modelMat)) * vec4(vertNormal, 1.0f)).xyz);
	texCoord = vertTexCoord;
	gl_Position = projMat * viewMat * modelMat * vec4(vertPos, 1.0f);
}