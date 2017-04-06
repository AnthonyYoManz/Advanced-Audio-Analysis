#include "BaseObject.h"
#include <glm/gtc/matrix_transform.hpp>
namespace dix
{
	void BaseObject::v_initialise(BaseMesh * _mesh)
	{

	}
	void BaseObject::v_cleanup()
	{
	}
	void BaseObject::v_draw()
	{
		if (m_mesh)
		{
			glBindVertexArray(m_mesh->getVAO());
			glDrawArrays(GL_TRIANGLES, 0, m_mesh->getVertexCount());
		}
	}

	void BaseObject::initialise(BaseMesh* _mesh)
	{
		m_mesh = _mesh;
		m_transform = glm::mat4(1.0f);
		v_initialise(_mesh);
	}

	void BaseObject::setMesh(BaseMesh * _mesh)
	{
		m_mesh = _mesh;
	}

	void BaseObject::cleanup()
	{
		v_cleanup();
		m_transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		m_mesh = nullptr;
	}

	void BaseObject::draw(GLuint _modelMatrixUniform)
	{
		glUniformMatrix4fv(_modelMatrixUniform, 1, NULL, &m_transform[0][0]);
		v_draw();
	} 
}