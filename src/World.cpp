#include "World.h"

Vector2 World::gravity = { 0, 9.8f };

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
	//for (auto& body : bodies) body.AddForce(gravity * 100.0f * body.gravityScale, ForceMode::Acceleration);// Vector2{ 0,0 };
	for (auto& body : bodies) body.AddForce(gravity * body.gravityScale, ForceMode::Acceleration);

	for (auto& effector : effectors) effector->Apply(bodies);


	// integration
	for (auto& body : bodies) if (body.bodyType == BodyType::Dynamic) SemiImplicitEuler(body, dt); // add to world update
	for (int i = 0; i < 4; i++) { //we can run these only 4 times to stop fps drops.
		UpdateCollision();

	}
}

void World::Draw()
{

	for (auto& effector : effectors) {
		effector->Draw();
	}
	for (auto& body : bodies) //draw in WORLD
	{
		body.DrawCircle(body.position, body.size, PURPLE);
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
		if (body.position.x - body.size > boundsMax.x) {
			body.position.x = boundsMax.x - body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.x - body.size < boundsMin.x) {
			body.position.x = boundsMin.x + body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.y - body.size > boundsMax.y) {
			body.position.y = GetScreenHeight() - body.size;
			body.velocity.y *= -body.restitution;
		}
		if (body.position.y - body.size < boundsMin.y) {
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
