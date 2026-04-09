#pragma once
#include "Effector.h"

class GravitationalEffector : public Effector
{
public:
    GravitationalEffector(float strength) : strength(strength) {}

    void Apply(std::vector<Physbody>& bodies) override;

private:
    float strength = 10.0f;
};