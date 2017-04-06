#version 430

uniform sampler2D tex;

layout(location = 0) out vec4 fragColour;
in vec4 colour;
in vec3 normal;
in vec2 texCoord;

uniform float textureWidth;
uniform float textureHeight;
uniform float sensitivity = 0.9f;
uniform vec4 outlineColour = {0.0f, 0.0f, 0.0f, 1.0f};

void main()
{
	float dx = 1.0f / textureWidth;
	float dy = 1.0f / textureHeight;
	vec4 current = texture(tex, texCoord);
	float n = 0;
	for(int ix = -1; ix <= 1; ix++ )
	{
		for(int iy = -1; iy <= 1; iy++)
		{
			float ox = clamp(texCoord.x + dx * ix, 0.0f, 1.0f);
			float oy = clamp(texCoord.y + dy * iy, 0.0f, 1.0f);
			vec3 norm = texture(tex, vec2(ox, oy)).rgb;
			norm = abs(current.rgb - norm);
			n = max( n, norm.x );
			n = max( n, norm.y );
			n = max( n, norm.z );
		}
	}
	n = step(1.0f - clamp(sensitivity, 0.0f, 1.0f), n);
	fragColour = vec4(outlineColour.rgb, n * outlineColour.a);
	
}