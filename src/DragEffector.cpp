#include "DragEffector.h"

void DragEffector::Apply(std::vector<Body>& ibodies)
{
	std::vector<Body*> obodies;
	CollectBodiesInside(ibodies, obodies);

	for (auto& body : obodies) {
		Vector2 force = Vector2Negate(body->velocity) * drag;
		body->AddForce(force);
	}
}

void DragEffector::Draw()
{
	Effector::Draw();
	DrawCircleV(position, size, Fade(YELLOW, 0.2f));
}
