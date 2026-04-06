#pragma once
#include <vector>
#include "Body.h"

class World {
public:
    World() {
		bodies.reserve(1000);
    }

    void Step(float dt);
    void Draw();
    void AddBody(const Body& body);
private:
    const Vector2 gravity = { 0, 9.81f };
    std::vector<Body> bodies;
};






