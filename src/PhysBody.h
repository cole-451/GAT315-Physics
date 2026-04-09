#pragma once

#include "raylib.h"
#include "raymath.h"
#include <vector>

enum class BodyType {
	Static,
	Kinematic,
	Dynamic
};

enum class ForceMode {
	Force,
	Acceleration,
	Impulse,
	VelocityChange
};



class Physbody {
public:
	Vector2 position{ 0,0 };
	Vector2 velocity{ 0,0 };
	Vector2 acceleration{ 0,0 };

	BodyType bodyType = BodyType::Dynamic;
	ForceMode forceMode = ForceMode::Force;
	float mass = 1.0f;;
	float inverseMass = 1.0f; // 1 / mass
	float size = 1.0f;
	float restitution = 1.0f;
	float gravityScale = 1.0f;
	float damping = 0.0f;


	

	void AddForce( Vector2 force, ForceMode forceMode = ForceMode::Force);

	void DrawCircle( Vector2 position, float size, Color color);



};