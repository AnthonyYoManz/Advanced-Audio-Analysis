#pragma once
#include <glm/matrix.hpp>
#include "BaseMesh.h"
namespace dix
{
	class BaseObject
	{
	protected:
		glm::mat4 m_transform;
		BaseMesh* m_mesh;
		//Initialise the object
		virtual void v_initialise(BaseMesh* _mesh);
		//Free object memory
		virtual void v_cleanup();
		//Draw object
		virtual void v_draw();
	public:
		//Initialise the object
		void initialise(BaseMesh* _mesh);
		//Assign a new mesh
		void setMesh(BaseMesh* _mesh);
		//Free dynamic object memory
		void cleanup();
		//Draw object
		void draw(GLuint _modelMatrixUniform);
	};
}