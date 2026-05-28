#pragma once
#include <vector>
#include "Body.h"
#include "GravitationalEffector.h"
#include "collision.h"
#include "Spring.h"

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
    void SetBounds(Vector2 min, Vector2 max) { boundsMin = min; boundsMax = max; }
    Body* GetBodyIntersect(Vector2 position);

	static void SetGravity(Vector2 newGravity) { gravity = newGravity; }
private:
    static Vector2 gravity;

    std::vector<Body> bodies;
	std::vector<Effector*> effectors;
    std::vector<Contact> contacts;
	std::vector<Spring*> springs; 
    Vector2 boundsMin{ -10.0f, -5.0f };
    Vector2 boundsMax{ 10.0f,  5.0f };
};






