#pragma once
#include "dix/BaseMesh.h"

class PlaneMesh : public dix::BaseMesh
{
protected: 
	void v_load() override;
public:
	PlaneMesh() = default;
	~PlaneMesh() = default;
};