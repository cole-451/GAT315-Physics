#include "GravitationalEffector.h"

void GravitationalEffector::Apply(std::vector<Physbody>& ibodies)
{
    std::vector<Physbody*> bodies;

    CollectBodiesInside(ibodies, bodies);

    for (size_t i = 0; i < bodies.size(); i++)
    {
        for (size_t j = i + 1; j < bodies.size(); j++)
        {
            Physbody& bodyA = *bodies[i];
            Physbody& bodyB = *bodies[j];

            // STEP 1: Direction vector
            Vector2 direction = bodyA.position - bodyB.position; //<direction vector points from bodyB to bodyA> (tail - head);

                // STEP 2: Distance
            float distance = Vector2Length(direction);

                // STEP 3: Clamp distance
            distance = fmaxf(distance, 1.0f); //<clamp distance to not go less than 1.0, use fmaxf()>;

                // STEP 4: Force magnitude
            float forceMagnitude = strength * ((bodyA.mass * bodyB.mass) / (distance * distance)) ; //<use formula in image above to compute force>;

            // STEP 5: Force vector
                Vector2 forceDirection = Vector2Normalize(direction) * forceMagnitude;

                // STEP 6: Apply equal and opposite forces
                bodyA.AddForce(forceDirection * -1);
                bodyB.AddForce(forceDirection * 1);
        }

    }
}

void GravitationalEffector::Draw() {
    Effector::Draw();
    DrawCircleV(position, size, Fade(ORANGE, 0.2f));
}
