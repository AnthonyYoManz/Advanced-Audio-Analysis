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
	texCoord = vertTexCoord;
	colour = vec4(0.0f, 0.0f, 0.0f, 1.0f);//vertColour;
	normal = vec3(0.0f, 0.0f, 1.0f);
	//gl_Position = vec4(vertPos, 1.0f);
	gl_Position = vec4(vertPos.xy, 0.0f, 1.0f);
}