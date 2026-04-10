#pragma once
#include <raylib.h>
#include <raymath.h>
	 
enum class BodyType
{
	STATIC,
	DYNAMIC,
	KINEMATIC
};

enum class ForceMode{
	Force,
	Impulse,
	VelocityChange,
	Acceleration
};

struct Body {  
	BodyType bodyType{ BodyType::DYNAMIC };
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	Vector2 acceleration{ 0, 0 };
	float mass{ 1.0f };
	float size{ 1.0f };
	float restitution{ 0.5f };
	float gravityScale{ 1.0f };
	float damping{ 0.5f };



	void AddForce(Vector2 force, ForceMode forceMode = ForceMode::Force);
	void Draw() const;
};

