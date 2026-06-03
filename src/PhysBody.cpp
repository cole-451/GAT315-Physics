#include "PhysBody.h"

void Physbody::AddForce( Vector2 force, ForceMode forceMode) {

	if (bodyType != BodyType::Dynamic) return;

	switch (forceMode)
	{
	case ForceMode::Force:
		acceleration += force * inverseMass;
		break;
	case ForceMode::Acceleration:
		acceleration += force;
		break;
	case ForceMode::Impulse:
		velocity += force * inverseMass;
		break;
	case ForceMode::VelocityChange:
		velocity += force;
		break;
	default:
		break;

	}
}

void Physbody::DrawCircle( Vector2 position, float size, Color color) {
	DrawCircleV(position, size, color);
	DrawCircleLinesV(position, size, color);
}