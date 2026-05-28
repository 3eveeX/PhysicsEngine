#include "AreaEffector.h"

void AreaEffector::Apply(std::vector<Body>& ibodies)
{
	std::vector<Body*> obodies;
	CollectBodiesInside(ibodies, obodies);

	for (auto& body : obodies) {
		Vector2 direction = Vector2{ cosf(angle * DEG2RAD), sinf(angle * DEG2RAD) };
		Vector2 force = direction * forceMagnitude;
		body->AddForce(force);
	}
}

void AreaEffector::Draw()
{
	Effector::Draw();
	DrawCircleV(position, size, Fade(GREEN, 0.2f));
}




