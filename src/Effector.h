#pragma once
#include "PhysBody.h"
#include <vector>

class Effector {
public:
	virtual void Apply(std::vector<Physbody>& bodies) = 0;

	virtual void Draw() {}

};