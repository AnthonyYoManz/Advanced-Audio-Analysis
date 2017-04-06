#pragma once
#include "dix/BaseMesh.h"

class CubeMesh : public dix::BaseMesh
{
protected:
	void v_load() override;
public:
	CubeMesh() = default;
	~CubeMesh() = default;
};