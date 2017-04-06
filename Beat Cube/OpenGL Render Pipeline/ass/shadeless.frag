#version 430

uniform sampler2D tex;

layout(location = 0) out vec4 fragColour;
in vec4 colour;
in vec3 normal;
in vec2 texCoord;

void main()
{
	fragColour = texture(tex, texCoord);
}