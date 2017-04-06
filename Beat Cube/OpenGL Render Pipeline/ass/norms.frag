#version 430

uniform sampler2D tex;

layout(location = 0) out vec4 fragColour;
in vec4 colour;
in vec3 normal;
in vec2 texCoord;

void main()
{
	vec3 norm = normal;
	norm.x += 1;
	norm.y += 1;
	norm.z += 1;
	norm /= 2.0f;
	fragColour = vec4(norm, 1.0f);
}