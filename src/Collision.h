#pragma once

#include "PhysBody.h"


struct Contact {
	Physbody* bodyA;
	Physbody* bodyB;

	float restitution;	// restitution of both bodies
	float depth;		// penetration depth
	Vector2 normal;		// normal contact vector

	static void CreateContacts(std::vector<Physbody>& bodies, std::vector<Contact>& contacts);
	static void SeparateContacts(std::vector<Contact>& contacts);
	static bool Intersects(const Physbody& bodyA, const Physbody& bodyB);
};