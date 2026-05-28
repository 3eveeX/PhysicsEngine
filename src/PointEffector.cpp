#include "PointEffector.h"

void PointEffector::Apply(std::vector<Body>& ibodies)
{
		std::vector<Body*> obodies;
		CollectBodiesInside(ibodies, obodies);

		for (auto& body : obodies) {
			Vector2 toBody = body->position - position;
			Vector2 force = Vector2Normalize(toBody) * forceMagnitude;
			body->AddForce(force);
		}
}

void PointEffector::Draw()
{
	Effector::Draw();
	DrawCircleV(position, size, Fade(RED, 0.2f));
}
