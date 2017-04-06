#include "PlaneMesh.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

void PlaneMesh::v_load()
{
	m_vertexCount = 6;
	m_triangleCount = 2;

	glm::vec3 verts[] =
	{
		glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, -1.0f, 0.0f)
	};
	/*glm::vec3 verts[] =
	{
		glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.5f, -0.5f, 0.0f)
	};*/

	glm::vec3 norms[] =
	{
		glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1)
	};

	glm::vec2 texCoords[] =
	{
		glm::vec2(0, 0), glm::vec2(1, 0),glm::vec2(0, 1),
		glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0)
	};

	glm::vec4 colours[] =
	{
		glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1),
		glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1)
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vertexCount, verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vertexCount, norms, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_vertexCount, texCoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * m_vertexCount, colours, GL_STATIC_DRAW);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NULL, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, NULL, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, NULL, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[3]);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, NULL, NULL);
}
