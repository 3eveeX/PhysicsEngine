#include "Body.h"




void Body::AddForce(Vector2 force, ForceMode forceMode)
{
	if (bodyType != BodyType::DYNAMIC) return;
	acceleration += force / mass;
}

void Body::Draw() const
{
	DrawCircleV(position, size, WHITE);
	DrawCircleLinesV(position, size, RED);
}


