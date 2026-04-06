#include "World.h"

void World::ExplicitEuler(Physbody& body, float dt) {
	body.position += body.velocity * dt;
	body.velocity += body.acceleration * dt;
}

void World::SemiImplicitEuler(Physbody& body, float dt) {
	body.velocity += body.acceleration * dt;
	body.position += body.velocity * dt;
}

void World::AddBody(Physbody& body) {
	bodies.push_back(body);
}