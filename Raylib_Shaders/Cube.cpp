#include "Cube.h"
#include <raylib.h>
#include <rlgl.h>

Cube::Cube() {
    mesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    material = LoadMaterialDefault();
}

void Cube::draw(Matrix matModel) {
    material.maps[MATERIAL_MAP_DIFFUSE].color = RED;
    DrawMesh(mesh, material, matModel);
    rlEnableWireMode();
        material.maps[MATERIAL_MAP_DIFFUSE].color = BLACK;
        DrawMesh(mesh, material, matModel); 
    rlDisableWireMode();
}