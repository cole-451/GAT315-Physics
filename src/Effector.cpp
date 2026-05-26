#include "Effector.h"

void Effector::Draw() {
	DrawCircleLinesV(position, size, ORANGE);
}

void Effector::CollectBodiesInside(std::vector<Physbody>& ibodies, std::vector<Physbody*>& obodies)
{
	for (auto& body : ibodies) {
		if (Vector2DistanceSqr(body.position, position) < (size * size)) {
			obodies.push_back(&body);
		}
	}
}
