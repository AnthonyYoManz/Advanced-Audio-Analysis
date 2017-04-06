#include "Framebuffer.h"
#include <iostream>

namespace dix
{
	void Framebuffer::genDepthBuffer(unsigned int _width, unsigned int _height, bool _asTexture)
	{
		if (_asTexture)
		{
			m_texDepthBuffer.create(dix::Vector2u(_width, _height), true);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texDepthBuffer.getHandle(), 0);
		}
		else
		{
			glGenRenderbuffers(1, &m_depthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
		}
	}

	void Framebuffer::genStencilBuffer(unsigned int _width, unsigned int _height)
	{
		glGenRenderbuffers(1, &m_stencilBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_stencilBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX, _width, _height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencilBuffer);
	}

	Framebuffer::Framebuffer()
	{
		m_depthBufferIsTexture = false;
		m_handle = 0;
		m_depthBuffer = 0;
		m_stencilBuffer = 0;
		m_defaultCamera = nullptr;
		m_size = Vector2u(0, 0);
	}

	Framebuffer::~Framebuffer()
	{
		cleanup();
	}

	void Framebuffer::initialise(unsigned int _width, unsigned int _height, 
								 FramebufferAttachment _attachments = FramebufferAttachment::NONE, 
								 bool _extraColourBuffer = false,
								 bool _depthBufferAsTexture = false)
	{
		m_defaultCamera = new Camera(Vector3f(0, 0, 0), Vector2f(_width, _height), IntRect(0, 0, _width, _height));
		m_size = Vector2u(_width, _height);
		m_depthBufferIsTexture = _depthBufferAsTexture;
		m_hasExtraColourBuffer = _extraColourBuffer;
		glGenFramebuffers(1, &m_handle);
		glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
		m_colourBuffer.create(Vector2u(_width, _height));
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colourBuffer.getHandle(), 0);
		if (_extraColourBuffer)
		{
			m_extraColourBuffer.create(Vector2u(_width, _height));
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_extraColourBuffer.getHandle(), 0);
		}
		if (_attachments == FramebufferAttachment::DEPTH_BUFFER)
		{
			genDepthBuffer(_width, _height, _depthBufferAsTexture);
		}
		else if (_attachments == FramebufferAttachment::STENCIL_BUFFER)
		{
			genStencilBuffer(_width, _height);
		}
		else if (_attachments == FramebufferAttachment::DEPTH_STENCIL_BUFFER)
		{
			genDepthBuffer(_width, _height, _depthBufferAsTexture);
			genStencilBuffer(_width, _height);
		}
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "FBO incomplete\n";
			std::cout << "Max size: " << GL_MAX_FRAMEBUFFER_WIDTH << "x" << GL_MAX_FRAMEBUFFER_HEIGHT << "\n";
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_UNSUPPORTED)
			{
				std::cout << "FBO unsupported\n";
			}
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
			{
				std::cout << "Missing attachment\n";
			}
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
			{
				std::cout << "Attachment incomplete\n";
			}
		}
		if (_extraColourBuffer)
		{
			GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
			glDrawBuffers(2, drawBuffers);
		}
		else
		{
			GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, drawBuffers);
		}
	}

	void Framebuffer::bindBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
	}

	void Framebuffer::cleanup()
	{
		if (m_handle != 0)
		{
			glDeleteFramebuffers(1, &m_handle);
			m_handle = 0;
		}
		m_colourBuffer.free();
		if (m_depthBufferIsTexture)
		{
			m_texDepthBuffer.free();
		}
		else
		{
			if (m_depthBuffer != 0)
			{
				glDeleteRenderbuffers(1, &m_depthBuffer);
				m_depthBuffer = 0;
			}
		}
		if (m_stencilBuffer != 0)
		{
			glDeleteRenderbuffers(1, &m_stencilBuffer);
			m_stencilBuffer = 0;
		}
		if (m_defaultCamera)
		{
			delete m_defaultCamera;
			m_defaultCamera = nullptr;
		}
	}

	const Texture& Framebuffer::getTexture() const
	{
		return m_colourBuffer;
	}

	const Texture& Framebuffer::getExtraTexture() const
	{
		return m_extraColourBuffer;
	}

	Texture* Framebuffer::getDepthBuffer()
	{
		if (m_depthBufferIsTexture)
		{
			return &m_texDepthBuffer;
		}
		return nullptr;
	}

	Camera* Framebuffer::getDefaultCamera()
	{
		return m_defaultCamera;
	}

	const Vector2u & Framebuffer::getSize()
	{
		return m_size;
	}
}