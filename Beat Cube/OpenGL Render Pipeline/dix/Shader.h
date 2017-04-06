#pragma once
#include <gl/glew.h>

namespace dix
{
	enum class ShaderType
	{
		VERTEX,
		FRAGMENT
	};

	class Shader
	{
	private:
		GLuint m_handle;
		ShaderType m_type;
	public:
		Shader();
		~Shader();

		void load(const char* _filename, ShaderType _type);
		void free();

		GLuint getHandle() const;
	};
}