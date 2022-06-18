#pragma once

#include "raylib.h"
#include "raymath.h"

class Effect {
    public:
        virtual void force(Vector3 *positions, Vector3 *velocities, size_t count, float dt);
        virtual void constraint(Vector3 *positions, Vector3 *velocities, size_t count, float dt);
};