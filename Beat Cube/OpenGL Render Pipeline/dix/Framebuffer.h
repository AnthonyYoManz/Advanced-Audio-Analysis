#pragma once

#include <GL/glew.h>
#include "Camera.h"
#include "Vector2.h"
#include "Texture.h"

namespace dix
{
	enum class FramebufferAttachment
	{
		NONE,
		DEPTH_BUFFER,
		STENCIL_BUFFER,
		DEPTH_STENCIL_BUFFER
	};

	class Framebuffer
	{
	private:
		bool m_depthBufferIsTexture;
		bool m_hasExtraColourBuffer;
		GLuint m_handle;
		Texture m_colourBuffer;
		Texture m_extraColourBuffer;
		Texture m_texDepthBuffer;
		GLuint m_depthBuffer;
		GLuint m_stencilBuffer;
		Camera* m_defaultCamera;
		Vector2u m_size;

		void genDepthBuffer(unsigned int _width, unsigned int _height, bool _asTexture);
		void genStencilBuffer(unsigned int _width, unsigned int _height);
	public:
		Framebuffer();
		~Framebuffer();

		void initialise(unsigned int _width, unsigned int _height, FramebufferAttachment _attachments, 
						bool _extraColourBuffer, bool _depthBufferAsTexture);
		void bindBuffer();
		void cleanup();
		
		//Returns the colour data
		const Texture& getTexture() const;
		//Returns the extra colour data
		const Texture& getExtraTexture() const;
		//Returns the depth buffer if it is stored as a texture. Otherwise returns nullptr.
		Texture* getDepthBuffer();
		Camera* getDefaultCamera();
		const Vector2u& getSize();
	};
}