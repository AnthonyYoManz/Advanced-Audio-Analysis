#version 430

layout(location = 0) out vec4 fragColour;
in vec4 colour;

void main()
{
	fragColour = colour;
}