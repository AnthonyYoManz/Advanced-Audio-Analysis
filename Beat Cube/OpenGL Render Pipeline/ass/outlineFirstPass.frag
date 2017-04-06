#version 430

uniform sampler2D tex;

layout(location = 0) out vec4 fragColour;
layout(location = 1) out vec4 fragNormal;
in vec4 colour;
in vec3 normal;
in vec2 texCoord;

void main()
{
	float intensity = clamp(dot(normal, vec3(0.0f, 0.0f, 1.0f)), 0.0f, 1.0f);
	fragColour = vec4(colour.rgb * texture(tex, texCoord).rgb * intensity, colour.a * texture(tex, texCoord).a);
	fragNormal = vec4(normal.rgb, 1.0f);
}