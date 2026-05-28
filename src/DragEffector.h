#pragma once
#include "Effector.h"
class DragEffector : public Effector
{
public:
	DragEffector(Vector2 position, float size, float drag) : drag(drag),
		Effector(position, size)
	{
	}

	void Apply(std::vector<Body>& bodies) override;
	void Draw();

private:
	float drag;
};
