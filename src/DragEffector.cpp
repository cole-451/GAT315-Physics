#include "DragEffector.h"

void DragEffector::Apply(std::vector<Physbody>& ibodies)
{
	std::vector<Physbody*> bodies;

	CollectBodiesInside(ibodies, bodies);

	for (auto& body : bodies) {
		Vector2 direction = body->position - position;

	//drag => F = -v*k
		Vector2 drag = (body->velocity * -1) * dragRate;
	Vector2 force = Vector2Negate(body->velocity) * drag;
		body->AddForce(force);

	}
}

void DragEffector::Draw() {
	Effector::Draw();
	DrawCircleV(position, size, Fade(YELLOW, 0.2f));
}
