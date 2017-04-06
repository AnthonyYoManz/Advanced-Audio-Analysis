#pragma once
#include <gl/glew.h>
#include "Vector2.h"

namespace dix
{
	class Texture
	{
	private:
		GLuint m_handle;
	public:
		Texture();
		~Texture();

		void load(const char* _filename);
		void create(Vector2u _size, bool _isDepthTexture = false);
		void create(Vector2u _size, float* _pixels);
		void free();
		void setLinearScaling(bool _linearScalingEnabled);
		GLuint getHandle() const;
	};
}