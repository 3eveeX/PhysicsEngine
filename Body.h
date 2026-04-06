#pragma once
#include <raylib.h>
#include <raymath.h>

struct Body {
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float mass;
	float size;
	float restitution;
	float gravityScale = 1.0f;
	float damping = 0.0f;
	
	void AddForce(Vector2 force);
	void Draw() const;
};

