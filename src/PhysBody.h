#pragma once

#include "raylib.h"
#include "raymath.h"
#include <vector>

class Physbody {
public:
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float mass = 1.0f;;
	float size = 1.0f;
	float restitution = 1.0f;
	float gravityScale = 1.0f;
	float damping = 0.0f;


	

	void AddForce( Vector2 force);

	void DrawCircle( Vector2 position, float size, Color color);



};