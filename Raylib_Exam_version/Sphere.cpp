#include "Sphere.h"
#include "raylib.h"
#include "rlgl.h"

Sphere::Sphere() {
    mesh = GenMeshSphere(0.5f, 10, 10);
    material = LoadMaterialDefault();
    material.maps[MATERIAL_MAP_DIFFUSE].color = RED;
}

void Sphere::draw(Matrix matModel) {
    //rlEnableWireMode();
    DrawMesh(mesh, material, matModel);
    //rlDisableWireMode();
}
