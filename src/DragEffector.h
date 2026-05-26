#pragma once
#include "Effector.h"

class DragEffector : public Effector {
	// Inherited via Effector
public:
	DragEffector(Vector2 position, float size, float drag) :
		Effector(position, size),
		dragRate{ drag }
		
	{
	}

	void Apply(std::vector<Physbody>& bodies) override;

	void Draw() override;
private:
	float dragRate;
};