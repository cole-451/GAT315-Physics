#pragma once
#include "Effector.h"

class AreaEffector : public Effector {
	// Inherited via Effector
public:
	AreaEffector(Vector2 position, float size, float angle, float forceMagnitude) :
		Effector(position, size),
		angle{angle},
		forceMagnitude{ forceMagnitude }
	{
	}

	void Apply(std::vector<Physbody>& bodies) override;

	void Draw() override;
private:
	float angle;
	float forceMagnitude = 1.0f;
};