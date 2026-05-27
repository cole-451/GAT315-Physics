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

	 static void SetGravity(Vector2 newgravity) { gravity = newgravity; }
	static Vector2 gravity;

	 std::vector<Physbody> bodies;

	 std::vector<class Effector*> effectors;

	 std::vector<Contact> contacts;

	 void Step(float dt);
	 void Draw();

	 void UpdateCollision();

	 void AddBody(Physbody& body);
	 void AddEffector(Effector* effector);

	 void SetBounds(Vector2 min, Vector2 max) { boundsMin = min; boundsMax = max; }

	 Physbody* GetBodyIntercept(Vector2& position);

 private:
	 Vector2 boundsMin{ -10.0f, -5.0f };
	 Vector2 boundsMax{ 10.0f,  5.0f };


};