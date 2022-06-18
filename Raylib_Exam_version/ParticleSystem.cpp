#include "ParticleSystem.h"
#include "raymath.h"
#include <random>

ParticleSystem::ParticleSystem(size_t count) {
    mesh = GenMeshSphere(0.02f, 8, 8);
    material = LoadMaterialDefault();
    material.maps[MATERIAL_MAP_DIFFUSE].color = BLACK;
    this->count = count;
    positions = new Vector3[count];
    velocities = new Vector3[count];
    springsForce = new Vector3[count];
}

ParticleSystem::ParticleSystem(Vector3* positions, Vector3* velocities, size_t count) : ParticleSystem(count) {
    setPositions(positions);
    setVelocities(velocities);
}

ParticleSystem::ParticleSystem(size_t count, Vector3 position, float deviation, Vector3 velocity, float velocityDeviation) : ParticleSystem(count) {
    netHeight = sqrt(count);
    netWidth  = sqrt(count);
    for (int i = 0; i < netHeight; i++) {
        for (int j = 0; j < netWidth; j++) {
            const int current = i * netHeight + j;
            positions[current] = { (float)i/5, (float)5, (float)j/5 };
            velocities[current] = { (float)0, (float)0, (float)0 };
        }
    }
}

void ParticleSystem::setPositions(Vector3* positions) {
    for(int i=0; i<count; i++) {
        this->positions[i] = positions[i];
    }
}

void ParticleSystem::setVelocities(Vector3* velocities) {
    for(int i=0; i<count; i++) {
        this->velocities[i] = velocities[i];
    }
}

void ParticleSystem::draw(Matrix matModel) {
    for(int i=0; i<count; i++) {
        DrawMesh(mesh, material, MatrixMultiply(matModel, MatrixTranslate(positions[i].x, positions[i].y, positions[i].z)));
    }
}

void ParticleSystem::update(float dt) {
    for (int i = 0; i < netHeight; i++) {
        for (int j = 0; j < netWidth; j++) {
            const int current = i * netHeight + j;

            //Add Springs
            const int left = current - 1;
            const int right = current + 1;
            const int top = current - netHeight;
            const int bottom = current + netHeight;
            const int topLeft = top - 1;
            const int topRight = top + 1;
            const int bottomLeft = bottom - 1;
            const int bottomRight = bottom + 1;
            const int rightRight = right + 1;
            const int bottomBottom = bottom + netHeight;

            //Structural springs
            if (j < netWidth - 1) {
                applySpringForce(current, right);
            }
            if (i < netHeight - 1) {
                applySpringForce(current, bottom);
            }


            //Shear springs
            if (i > 0 && j < netWidth - 1) {
                applySpringForce(current, topRight);
            }
            if (i < netHeight - 1 && j < netWidth - 1) {
                applySpringForce(current, bottomRight);
            }


            //Bending Springs
            if (j < netWidth - 2) {
                applySpringForce(current, rightRight);
            }
            if (i < netHeight - 2) {
                applySpringForce(current, bottomBottom);
            }
        }
    }
    for(Force *force : forces) {
        force->apply(positions, velocities, count, dt);
    }

    for (int i = 0; i < count; i++) {
        positions[i] = Vector3Add(positions[i], Vector3Scale(velocities[i], dt));
        checkCollisionWithSphere(0.01f,i); 
       /* bool collisionS = false;
        if (CheckCollisionSpheres({ 1.0f, 1.0f, 1.0f }, 2.0f, positions[i],0.05f)){
            collisionS = true;
        }
        if (collisionS) {

            velocities[i] = Vector3Add(velocities[i], Vector3Scale({ 0.0f, 0.0f, 0.0f }, GetFrameTime()));
            positions[i] = Vector3Add(positions[i], Vector3Scale(velocities[i], dt));
            positions[i] = Vector3Add(positions[i], Vector3Scale(normal, -1.9 * dist));
        }
        else {
            positions[i] = Vector3Add(positions[i], Vector3Scale(velocities[i], dt));
        }*/
    }
    for(Collider *collider : colliders) {
        collider->collide(positions, velocities, count);
    }
}

void ParticleSystem::addForce(Force *force) {
    forces.push_back(force);
}

void ParticleSystem::addCollider(Collider *collider) {
    colliders.push_back(collider);
}

void ParticleSystem::applySpringForce(int p1, int p2) {

    //The distance between both particles in the spring
    float ex = positions[p2].x - positions[p1].x;
    float ey = positions[p2].y - positions[p1].y;
    float ez = positions[p2].z - positions[p1].z;

    float length = sqrt(pow(ex, 2) + pow(ey, 2) + pow(ez, 2));

    //Normalize the vector
    ex = ex / length;
    ey = ey / length;
    ez = ez / length;

    //Calculate Vi scalars
    float v1 = ex * velocities[p1].x + ey * velocities[p1].y + ez * velocities[p1].z;
    float v2 = ex * velocities[p2].x + ey * velocities[p2].y + ez * velocities[p2].z;
 
    float fSD = -25.0f * (0.3f - length) - 0.7f * (v1 - v2);

    float fx = fSD * ex;
    float fy = fSD * ey;
    float fz = fSD * ez;

    //springsForce
    velocities[p1] = Vector3Add(velocities[p1], Vector3Scale({ fx, fy, fz }, 0.012));
    velocities[p2] = Vector3Add(velocities[p2], Vector3Scale({ -fx, -fy, -fz }, 0.012));
    //velocities[p1] = Vector3Add(velocities[p1], Vector3Scale({ fx, fy, fz }, GetFrameTime()));
    //velocities[p2] = Vector3Add(velocities[p2], Vector3Scale({ -fx, -fy, -fz }, GetFrameTime()));
    
    DrawLine3D(positions[p1], positions[p2], BLACK);
}

void ParticleSystem::checkCollisionWithSphere(float radius, int particlePos)
{
    float penDist;
    Vector3 spherePos = {1.0f,2.0f,1.0f};
    Vector3 dist = { 0.0f,0.0f,0.0f };
    dist.x = spherePos.x - positions[particlePos].x;
    dist.y = spherePos.y - positions[particlePos].y;
    dist.z = spherePos.z - positions[particlePos].z;
    float length = sqrt((dist.x * dist.x) + (dist.y * dist.y) + (dist.z * dist.z));
    penDist = length - (radius + 1.0f);
    dist.x = dist.x / length;
    dist.y = dist.y / length;
    dist.z = dist.z / length;

    Vector3 P = {0.0f,0.0f,0.0f};
    P.x = dist.x * penDist;
    P.y = dist.y * penDist;
    P.z = dist.z * penDist;
    
    if (penDist < 0)
    {
        positions[particlePos].x += P.x;
        positions[particlePos].y += P.y;
        positions[particlePos].z += P.z;
        
        velocities[particlePos].x += 0;
        velocities[particlePos].y += 0;
        velocities[particlePos].z += 0;
    }
}