#include "Texture.h"
namespace dix
{
	Texture::Texture()
	{
		m_handle = 0;
	}

	Texture::~Texture()
	{
		free();
	}

	void Texture::load(const char * _filename)
	{
		//do this @ some point
	}

	void Texture::create(Vector2u _size, bool _isDepthTexture)
	{
		free();
		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_2D, m_handle);
		if (_isDepthTexture)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, _size.m_x, _size.m_y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.m_x, _size.m_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void Texture::create(Vector2u _size, float * _pixels)
	{
		free();
		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_2D, m_handle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.m_x, _size.m_y, 0, GL_RGBA, GL_FLOAT, _pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void Texture::free()
	{
		if (m_handle != 0)
		{
			glDeleteTextures(1, &m_handle);
			m_handle = 0;
		}
	}

	void Texture::setLinearScaling(bool _enable)
	{
		glBindTexture(GL_TEXTURE_2D, m_handle);
		if (_enable)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
	}

	GLuint Texture::getHandle() const
	{
		return m_handle;
	}
}
