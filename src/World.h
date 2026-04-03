#pragma once

#include "PhysBody.h"
#include "raylib.h"
#include "raymath.h"
#include <vector>

static class World {
public:

	static void ExplicitEuler(Physbody& body, float dt);

	static void SemiImplicitEuler(Physbody& body, float dt);

	Vector2 gravity{ 0, 9.81f };

	static std::vector<Physbody> bodies;


};