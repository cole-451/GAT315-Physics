#pragma once
#include "PhysBody.h"
#include "raylib.h"
class Spring {
public:
	Physbody* bodyA;
	Physbody* bodyB;

	float restLength;

	float stiffness;

	float damping;

public:

	Spring() = default;

	// if it can be null, pass in pointers instead of references
	Spring(Physbody* bodyA, Physbody* bodyB, float restLength, float stiffness = 1, float damping = 1) :
		bodyA{ bodyA },
		bodyB{ bodyB },
		restLength{ restLength },
		stiffness{ stiffness },
		damping{ damping }
		{}

	void Apply(float multiplier = 1);

	void Draw();

	
	

	static Vector2 GetSpringForce(Vector2 positionA, Vector2 positionB, float restLength, float stiffness = 1);


};