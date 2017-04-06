#include "ShaderProgram.h"
#include <iostream>

dix::ShaderProgram::ShaderProgram()
{
	m_handle = 0;
}

dix::ShaderProgram::~ShaderProgram()
{
	cleanup();
}

void dix::ShaderProgram::initialise(const Shader& _vertShader, const Shader& _fragShader)
{
	cleanup();
	m_handle = glCreateProgram();
	if (m_handle == 0)
	{
		std::cout << "Error creating program.\n";
		return;
	}
	glAttachShader(m_handle, _vertShader.getHandle());
	glAttachShader(m_handle, _fragShader.getHandle());
	glLinkProgram(m_handle);
	GLint param = GL_TRUE;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &param);
	if (param == GL_FALSE)
	{
		std::cout << "Shader program failed to link, please read the info log:\n";
		GLint maxInfoLogLength = 0;
		glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &maxInfoLogLength);
		GLchar* infoLog = new char[maxInfoLogLength];
		glGetProgramInfoLog(m_handle, maxInfoLogLength, NULL, infoLog);
		std::cout << infoLog << "\n";
		cleanup();
	}
}

void dix::ShaderProgram::cleanup()
{
	if (m_handle != 0)
	{
		glDeleteProgram(m_handle);
		m_handle = 0;
	}
	glUseProgram(NULL);
}

bool dix::ShaderProgram::findUniform(std::string _uniformName, UniformType _type)
{
	GLint uniformLocation = glGetUniformLocation(m_handle, _uniformName.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "Uniform '" << _uniformName << "' not found.\n";
		return false;
	}
	m_uniforms[_uniformName].m_location = uniformLocation;
	m_uniforms[_uniformName].m_type = _type;
	return true;
}

void dix::ShaderProgram::setUniform(std::string _uniformName, void* _data)
{
	glUseProgram(m_handle);
	auto uniformIt = m_uniforms.find(_uniformName);
	if (uniformIt == m_uniforms.end())
	{
		std::cout << "Uniform '" << _uniformName << "' is cannot be set as it is unknown.\n";
		return;
	}
	GLint uniformLocation = (*uniformIt).second.m_location;

	switch ((*uniformIt).second.m_type)
	{
	case UniformType::FLOAT: 
		glUniform1f(uniformLocation, *((GLfloat*)_data));
		break;
	case UniformType::VEC2: 
		glUniform2fv(uniformLocation, 1, (GLfloat*)_data);
		break;
	case UniformType::VEC3: 
		glUniform3fv(uniformLocation, 1, (GLfloat*)_data);
		break;
	case UniformType::VEC4: 
		glUniform4fv(uniformLocation, 1, (GLfloat*)_data);
		break;
	case UniformType::MAT3:
		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, (GLfloat*)_data);
		break;
	case UniformType::MAT4:
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, (GLfloat*)_data);
		break;
	default: 
		break;
	}
	glUseProgram(NULL);
}

void dix::ShaderProgram::use()
{
	glUseProgram(m_handle);
}

GLuint dix::ShaderProgram::getHandle() const
{
	return m_handle;
}
