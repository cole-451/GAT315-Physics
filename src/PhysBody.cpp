#include "PhysBody.h"

void Physbody::AddForce( Vector2 force) {
	acceleration += force / mass;
}

void Physbody::DrawCircle( Vector2 position, float size, Color color) {
	DrawCircleV(position, size, color);
}