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
	//gravity update???
		//reset acceleration (world) update
	for (auto& body : bodies) body.acceleration = Vector2{ 0,0 };// Vector2{ 0,0 };
	for (auto& body : bodies) body.AddForce(gravity * 100.0f * body.gravityScale, ForceMode::Acceleration);// Vector2{ 0,0 };

	for (auto& effector : effectors) effector->Apply(bodies);

	/*if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		Vector2 pos = GetMousePosition();
		for (auto& body : bodies) {
			Vector2 direction = body.position - pos;
			if (Vector2Length(direction) <= 100.0f) {
				Vector2 force = Vector2Normalize(direction) * -10000.0f;
				body.AddForce(force);
			}
		}

		DrawCircleLinesV(pos, 100, WHITE);
	}*/

	// integration
	for (auto& body : bodies) if(body.bodyType == BodyType::Dynamic) SemiImplicitEuler(body, dt); // add to world update

	UpdateCollision();
}

void World::Draw()
{
	for (auto& body : bodies) //draw in WORLD
	{
		body.DrawCircle(body.position, body.size, PURPLE);
	}

	for (auto& effector : effectors) {
		effector->Draw();
	}
}

void World::UpdateCollision()
{
	contacts.clear();
	Contact::CreateContacts(bodies, contacts);
	Contact::SeparateContacts(contacts);
	Contact::ResolveContacts(contacts);

	//barrier check: perhaps add to World
	for (auto& body : bodies)
	{
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

void World::AddBody(Physbody& body) {
	bodies.push_back(body);
}

void World::AddEffector(Effector* effector)
{
	effectors.push_back(effector);
}
