#include "Gravity.h"

Gravity::Gravity(Vector3 g) {
    this->g = g;
}

void Gravity::apply(Vector3 *positions, Vector3 *velocities, size_t count, float dt) {
    for(int i=0; i < count; i++) {
        velocities[i] = Vector3Add(velocities[i], Vector3Scale(g, dt));
    }
}