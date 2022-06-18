#include "Plan.h"
#include <iostream>

Plan::Plan(float a, float b, float c, float d) {
    normal = {a, b, c};
    float length = Vector3Length(normal);
    normal = Vector3Scale(normal, 1.0f/length);
    this->d = d/length;
}

void Plan::collide(Vector3 *positions, Vector3 *velocities, size_t count) {
    for(int i=0; i<count; i++) {
        float dist = positions[i].x * normal.x + positions[i].y * normal.y + positions[i].z * normal.z + d;
        if(dist < 0) {
            velocities[i] = Vector3Scale(Vector3Reflect(velocities[i], normal), 0.0f); //VENOM mod: change to 1.0 
            positions[i] = Vector3Add(positions[i], Vector3Scale(normal, -1.9*dist));
        }
    }
}