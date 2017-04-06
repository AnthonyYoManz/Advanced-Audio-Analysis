#pragma once
#include <map>
#include <string>
#include "Shader.h"
#include "UniformType.h"

namespace dix
{
	class ShaderProgram
	{
	private:
		struct UniformInfo
		{
			GLint m_location;
			UniformType m_type;
		};
		std::map<std::string, UniformInfo> m_uniforms;
		GLuint m_handle;
	public:
		ShaderProgram();
		~ShaderProgram();
		void initialise(const Shader& _vertShader, const Shader& _fragShader);
		void cleanup();
		bool findUniform(std::string _uniformName, UniformType _type);
		
		void setUniform(std::string _uniformName, void* _data);
		void use();
		
		GLuint getHandle() const;
	};
}