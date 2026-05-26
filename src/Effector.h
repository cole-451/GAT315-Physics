#pragma once
#include "PhysBody.h"
#include <vector>

 enum class EffectorType
	{
		Gravitation,
		Point,
		Area,
		Drag
	};
class Effector {
public:
	virtual void Apply(std::vector<Physbody>& bodies) = 0;

	

	Effector(Vector2 position, float size) : position{ position }, size{ size } {}

	virtual void Draw();
	
	 void CollectBodiesInside(std::vector<Physbody>& ibodies, std::vector<Physbody*>& obodies);
	
protected:
	Vector2 position;
	float size = 1.0f;

};