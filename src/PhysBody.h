#pragma once

#include "raylib.h"
#include "raymath.h"
#include <vector>

class Physbody {
public:
	Vector2 position;
	Vector2 velocity;
	float mass;
	Vector2 acceleration;
	float size;
	float restitution;


	

	void AddForce( Vector2 force);

	void DrawCircle( Vector2 position, float size, Color color);



};