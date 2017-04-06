#version 430
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec2 vertTexCoord;
layout(location = 3) in vec4 vertColour;

out vec4 colour;

void main()
{
	colour = vertColour;
	gl_Position = vec4(vertPos, 1.0f);
}