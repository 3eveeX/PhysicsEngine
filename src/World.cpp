#include "World.h"
#include "Integrator.h"

void World::Step(float dt)
{

	for (auto& body : bodies) body.acceleration = gravity * body.gravityScale;
	for (auto& body : bodies) body.AddForce(World::gravity * body.gravityScale * 100.0f);
	for (auto& effector : effectors) effector->Apply(bodies);

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		Vector2 mousePos = GetMousePosition();
		for (auto& body : bodies)
		{
			Vector2 toMouse = mousePos - body.position;
			float distance = Vector2Length(toMouse);
			if (distance <= 100)
			{
				Vector2 direction = Vector2Normalize(toMouse) * 300000.0f;
				body.AddForce(direction);
			}
		}
		DrawCircleLinesV(mousePos, 100, RED);
	}

	for (auto& body : bodies) SemiImplicitEuler(body, dt);

	UpdateCollision();
}

void World::Draw()
{
	for (const auto& body : bodies)
	{

		body.Draw();
	}
}	

void World::UpdateCollision()
{
	contacts.clear();
	CreateContacts(bodies, contacts);
	SeparateContacts(contacts);

	// collision
	for (auto& body : bodies)
	{
		if (body.position.x + body.size > GetScreenWidth())
		{
			body.position.x = GetScreenWidth() - body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.x - body.size < 0)
		{
			body.position.x = body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.y + body.size > GetScreenHeight())
		{
			body.position.y = GetScreenHeight() - body.size;
			body.velocity.y *= -body.restitution;
		}
		if (body.position.y - body.size < 0)
		{
			body.position.y = body.size;
			body.velocity.y *= -body.restitution;
		}
	}
}

void World::AddBody(const Body& body)
{
	bodies.push_back(body);
}
