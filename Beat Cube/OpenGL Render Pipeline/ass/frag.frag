#version 430

uniform sampler2D tex;

layout(location = 0) out vec4 fragColour;
in vec4 colour;
in vec3 normal;
in vec2 texCoord;

void main()
{
	float intensity = clamp(dot(normal, vec3(0.0f, 0.0f, 1.0f)), 0.0f, 1.0f);
	fragColour = vec4(colour.rgb * texture(tex, texCoord).rgb * intensity, colour.a * texture(tex, texCoord).a);
	//fragColour = vec4(normal.xyz, 1.0f);
}