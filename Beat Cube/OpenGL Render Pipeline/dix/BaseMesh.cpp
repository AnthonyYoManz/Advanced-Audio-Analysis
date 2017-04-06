#include "BaseMesh.h"
namespace dix
{
	void BaseMesh::load()
	{
		if (m_loaded)
		{
			unload();
		}

		m_vertexCount = 0;
		m_triangleCount = 0;
		glGenBuffers(4, m_vbo);
		glGenVertexArrays(1, &m_vao);

		v_load();

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		m_loaded = true;
	}

	void BaseMesh::unload()
	{
		if (m_loaded)
		{
			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(4, m_vbo);
			m_vertexCount = 0;
			m_triangleCount = 0;
			m_loaded = false;
		}
	}

	GLuint BaseMesh::getVAO()
	{
		return m_vao;
	}

	GLuint BaseMesh::getVertexVBO()
	{
		return m_vbo[0];
	}

	GLuint BaseMesh::getNormalVBO()
	{
		return m_vbo[1];
	}

	GLuint BaseMesh::getTextureCoordVBO()
	{
		return m_vbo[2];
	}

	GLuint BaseMesh::getColourVBO()
	{
		return m_vbo[3];
	}

	unsigned int BaseMesh::getVertexCount()
	{
		return m_vertexCount;
	}

	unsigned int BaseMesh::getTriangleCount()
	{
		return m_triangleCount;
	}
}