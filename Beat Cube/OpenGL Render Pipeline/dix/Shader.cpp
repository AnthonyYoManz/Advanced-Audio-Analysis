#include "Shader.h"
#include "FileLoader.h"

namespace dix
{
	Shader::Shader()
	{
		m_handle = 0;
	}

	Shader::~Shader()
	{
		free();
	}

	void Shader::load(const char* _filename, ShaderType _type)
	{
		m_type = _type;
		dix::FileLoader shaderLoader;
		const char* shaderSrc = shaderLoader.loadFile(_filename);
		if (_type == ShaderType::VERTEX)
		{
			m_handle = glCreateShader(GL_VERTEX_SHADER);
		}
		else if (_type == ShaderType::FRAGMENT)
		{
			m_handle = glCreateShader(GL_FRAGMENT_SHADER);
		}
		glShaderSource(m_handle, 1, &shaderSrc, NULL);
		glCompileShader(m_handle);
		GLint param = -1;
		glGetShaderiv(m_handle, GL_COMPILE_STATUS, &param);
		if (param == GL_FALSE)
		{
			std::cout << "Shader '" << _filename << "'failed to compile\n";
			GLint infoLogLength = 0;
			glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* infoLog = new char[infoLogLength];
			glGetShaderInfoLog(m_handle, infoLogLength, NULL, infoLog);
			std::cout << infoLog << "\n";
			delete[] infoLog;
		}
	}

	void Shader::free()
	{
		if (m_handle != 0)
		{
			glDeleteShader(m_handle);
			m_handle = 0;
		}
	}

	GLuint Shader::getHandle() const
	{
		return m_handle;
	}
}