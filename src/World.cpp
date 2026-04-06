#include "World.h"

void World::ExplicitEuler(Physbody& body, float dt) {
	body.position += body.velocity * dt;
	body.velocity += body.acceleration * dt;
	body.velocity *= (1.0f / (1.0f + body.damping * dt));
}

void World::SemiImplicitEuler(Physbody& body, float dt) {
	body.velocity += body.acceleration * dt;
	body.velocity *= (1.0f / (1.0f + body.damping * dt));
	body.position += body.velocity * dt;
}

void World::Step(float dt)
{
	//update

		//gravity update???
		//reset acceleration (world) update
	for (auto& body : bodies) body.acceleration = gravity * 100.0f * body.gravityScale;// Vector2{ 0,0 };

	//for (auto& body : world.bodies) body.AddForce(world.gravity * 100.0f);


	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		Vector2 pos = GetMousePosition();
		for (auto& body : bodies) {
			Vector2 direction = pos - body.position;
			if (Vector2Length(direction) <= 100.0f) {
				Vector2 force = Vector2Normalize(direction) * -10000.0f;
				body.AddForce(force);
			}
		}

		DrawCircleLinesV(pos, 100, WHITE);
	}

	for (auto& body : bodies) SemiImplicitEuler(body, dt); // add to world update


	//barrier check: perhaps add to World
	for (auto& body : bodies)
	{
		//integration
		SemiImplicitEuler(body, dt);

		if (body.position.x - body.size > GetScreenWidth()) {
			body.position.x = GetScreenWidth() - body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.x - body.size < 0) {
			body.position.x = body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.y - body.size > GetScreenHeight()) {
			body.position.y = GetScreenHeight() - body.size;
			body.velocity.y *= -body.restitution;
		}
		if (body.position.y - body.size < 0) {
			body.position.y = body.size;
			body.velocity.y *= body.restitution;
		}
	}
}

void World::Draw()
{
	for (auto& body : bodies) //draw in WORLD
	{
		body.DrawCircle(body.position, body.size, PURPLE);
	}
}

void World::AddBody(Physbody& body) {
	bodies.push_back(body);
}