#pragma once
#include "dix/BaseMesh.h"

class TriangleMesh : public dix::BaseMesh
{
protected:
	void v_load() override;
public:
	TriangleMesh() = default;
	~TriangleMesh() = default;
};