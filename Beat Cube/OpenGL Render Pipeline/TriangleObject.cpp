#include "TriangleObject.h"
#include "TriangleMesh.h"

void TriangleObject::v_initialise(dix::BaseMesh* _mesh = nullptr)
{
	m_mesh = new TriangleMesh;
	m_mesh->load();
}

void TriangleObject::v_cleanup()
{
	if (m_mesh)
	{
		m_mesh->unload();
		delete m_mesh;
		m_mesh = nullptr;
	}
}
