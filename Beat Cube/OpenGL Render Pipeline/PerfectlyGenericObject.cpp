#include "PerfectlyGenericObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include "CubeMesh.h"

void PerfectlyGenericObject::tick(float _dt)
{
	m_transform = glm::rotate(m_transform, 1.0f * _dt, glm::vec3(0.0f, 1.0f, 0.0f));
}

void PerfectlyGenericObject::setScale(float _scale)
{
	m_transform = glm::scale(glm::mat4(1.0f), glm::vec3(_scale, _scale, _scale));
}
