#pragma once

#include "PhysBody.h"
#include "raylib.h"
#include "raymath.h"
#include "Effector.h"
#include "Collision.h"
#include <vector>

 class World {
public:

	 void ExplicitEuler(Physbody& body, float dt);

	 void SemiImplicitEuler(Physbody& body, float dt);

	Vector2 gravity{ 0, 9.81f };

	 std::vector<Physbody> bodies;

	 std::vector<class Effector*> effectors;

	 std::vector<Contact> contacts;

	 void Step(float dt);
	 void Draw();

	 void UpdateCollision();

	 void AddBody(Physbody& body);
	 void AddEffector(Effector* effector);


};