#include "collision.h"




void CreateContacts(std::vector<Body>& bodies, std::vector<Contact>& contacts)
{
	for (int i = 0; i < bodies.size(); i++)
	{
		for (int j = i + 1; j < bodies.size(); j++)
		{
			Body& bodyA = bodies[i];
			Body& bodyB = bodies[j];

			if (bodyA.bodyType != BodyType::DYNAMIC && bodyB.bodyType != BodyType::DYNAMIC) continue;

			if (Intersects(bodyA, bodyB))
			{
				Contact contact;
				contact.bodyA = &bodyA;
				contact.bodyB = &bodyB;

				Vector2 direction = bodyA.position - bodyB.position;
				float distance = Vector2Length(direction);

				

					float radius = bodyA.size + bodyB.size;
					contact.depth = radius - distance;
					contact.normal = Vector2Normalize(direction);
					contact.restitution = (bodyA.restitution + bodyB.restitution) * 0.5f;

					contacts.push_back(contact);
			}
		}
	}

}

void SeparateContacts(std::vector<Contact>& contacts)
{
	for (auto& contact : contacts)
	{
		float totalInverseMass = 1 /contact.bodyA -> mass + 1 / contact.bodyB->mass;
			Vector2 separation = contact.normal * (contact.depth / totalInverseMass);
		contact.bodyA->position = contact.bodyA->position + (separation * 1/contact.bodyA->mass);
		contact.bodyB->position = contact.bodyB->position - (separation * 1/contact.bodyB->mass);
	}
}

bool Intersects(const Body& bodyA, const Body& bodyB)
{
	float distance = Vector2Distance(bodyA.position, bodyB.position);
	float radius = bodyA.size + bodyB.size;

	return (distance <= radius);
}