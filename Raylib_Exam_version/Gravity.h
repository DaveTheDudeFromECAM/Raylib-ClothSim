#pragma once

#include "Force.h"

class Gravity : public Force {
    private:
        Vector3 g;

    public:
        Gravity(Vector3 g);
        void apply(Vector3 *positions, Vector3 *velocities, size_t count, float dt);
};