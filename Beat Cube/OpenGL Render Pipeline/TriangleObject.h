#pragma once
#include "dix/BaseObject.h"

class TriangleObject : public dix::BaseObject
{
protected:
	void v_initialise(dix::BaseMesh* _mesh) override;
	void v_cleanup() override;
};