#include <raylib.h>
#include "rlgl.h"
#include "Cube.h"
#include "ModelObject.h"
#include <raymath.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "LUR - Scene Example");

    Camera camera = { 0 };
    camera.position = { 5.0f, 5.0f, 5.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FREE); 
    SetCameraPanControl(3);
    SetTargetFPS(60);

    Object scene = Object();

    Model model = LoadModel("assets/models/bunny.obj");

    MeshTangents(model.meshes);

    Texture texture = LoadTexture("assets/textures/stone_wall/cgaxis_pbr_17_stone_wall_5_diffuse.png");
    Shader shader = LoadShader("assets/shaders/base.vs", "assets/shaders/base.fs");

    model.materials[0].shader = shader;
    model.materials[0].shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(model.materials[0].shader, "matModel");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    int lightPosLoc = GetShaderLocation(shader, "lightPos");
    float lightPos[] = { 0.0f, 5.0f, 5.0f };
    SetShaderValue(shader, lightPosLoc, lightPos, SHADER_UNIFORM_VEC3);

    ModelObject bunny = ModelObject(model);
    bunny.scale(10.0f);

    scene.add(&bunny);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                DrawGrid(10, 1.0f);

                scene.render();
                bunny.rotateY(0.01);
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}