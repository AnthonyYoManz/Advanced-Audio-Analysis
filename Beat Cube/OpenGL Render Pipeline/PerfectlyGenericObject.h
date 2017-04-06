#pragma once
#include "dix/BaseObject.h"

class PerfectlyGenericObject : public dix::BaseObject
{
public:
	void tick(float _dt);
	void setScale(float _scale);
};