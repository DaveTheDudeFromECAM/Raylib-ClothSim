#pragma once

#include "raylib.h"
#include "raymath.h"

class Collider {
    public:
        virtual void collide(Vector3 *positions, Vector3 *velocities, size_t count) = 0;
};