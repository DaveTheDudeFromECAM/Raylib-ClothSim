#pragma once

#include "raylib.h"
#include "raymath.h"

class Force {
    public:
        virtual void apply(Vector3 *positions, Vector3 *velocities, size_t count, float dt) = 0;
};