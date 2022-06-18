#pragma once

#include "Collider.h"

class Plan : public Collider {
    private:
        Vector3 normal;
        float d;

    public:
        Plan(float a, float b, float c, float d);
        void collide(Vector3 *positions, Vector3 *velocities, size_t count);
};