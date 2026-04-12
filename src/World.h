#pragma once
#include <vector>
#include "Body.h"
#include "GravitationalEffector.h"
#include "collision.h"

class World {
public:
    World() {
		bodies.reserve(1000);
    }

    void Step(float dt);
    void Draw();
    void AddBody(const Body& body);

	void AddEffector(Effector* effector) { effectors.push_back(effector); }
    void UpdateCollision();
private:
    const Vector2 gravity = { 0.0f, 9.81f };
    std::vector<Body> bodies;
	std::vector<Effector*> effectors;
    std::vector<Contact> contacts;
};






