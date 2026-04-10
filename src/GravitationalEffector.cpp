#include "GravitationalEffector.h"
#include <raymath.h> 

void GravityEffector::Apply(std::vector<Body>& bodies)
{
    for (int i = 0; i < bodies.size(); ++i)
    {
        for (int j = i + 1; j < bodies.size(); ++j)
        {
            Body& bodyA = bodies[i];
            Body& bodyB = bodies[j];

            // STEP 1: Direction vector
            Vector2 direction = Vector2Subtract(bodyB.position, bodyA.position);

            // STEP 2: Distance
            float distance = Vector2Length(direction);

            // STEP 3: Clamp distance
            distance = fmaxf(distance, 1.0f);

            // STEP 4: Force magnitude (Newton's law of universal gravitation)
            float forceMagnitude = strength * (bodyA.mass * bodyB.mass) / (distance * distance);

            // STEP 5: Force vector
            Vector2 force = Vector2Scale(Vector2Normalize(direction), forceMagnitude);

            // STEP 6: Apply equal and opposite forces
            bodyA.AddForce(Vector2Scale(force, 1.0f));
            bodyB.AddForce(Vector2Scale(force, -1.0f));
        }
    }
}
