#pragma once
#include "Body.h"

inline void ExplicitEuler(Body& body, float deltaTime)
{
	body.position += body.velocity * deltaTime;
	body.velocity += body.acceleration * deltaTime;
	body.velocity *= (1.0f / (1.0f + body.damping * deltaTime));
}

inline void SemiImplicitEuler(Body& body, float deltaTime)
{
	body.velocity += body.acceleration * deltaTime;
	body.velocity *= (1.0f / (1.0f + body.damping * deltaTime));
	body.position += body.velocity * deltaTime;
}
	

