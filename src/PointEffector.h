#pragma once
#include "Effector.h"

class PointEffector : public Effector {
	// Inherited via Effector
public:
	PointEffector(Vector2 position, float size, float forceMagnitude) :
		Effector(position, size),
		forceMagnitude{forceMagnitude}
	{ }

	void Apply(std::vector<Physbody>& bodies) override;

	void Draw() override;
private:
	
	float forceMagnitude = 1.0f;
};