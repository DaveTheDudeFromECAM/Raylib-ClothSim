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

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

    Vector3 ballPosition = { 0.0f, 0.0f, 0.0f };
    Vector3 ballSpeed = { 1.5f, 1.0f, 1.0f };
    float ballRadius = 0.1f; 

    Vector3 ballPosition1 = { 0.5f, 0.0f, 0.0f };
    Vector3 ballSpeed1 = { 1.5f, 1.8f, 1.0f };

    Vector3 gravity = { -2.0f, -9.81f, 0.0f };
    
    SetCameraMode(camera, CAMERA_FREE); 
    SetCameraPanControl(3);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera);
        // Move sphere
        //------------------------------BALL---------------------------------------------------
        ballSpeed.x += (GetFrameTime() * gravity.x);
        ballSpeed.y += (GetFrameTime() * gravity.y);
        ballSpeed.z += (GetFrameTime() * gravity.z);
        ballPosition.x += GetFrameTime() * ballSpeed.x;
        ballPosition.y += GetFrameTime() * ballSpeed.y;
        ballPosition.z += GetFrameTime() * ballSpeed.z;
        //---------------------------------------------------------------------------------
        if ((ballPosition.x <= ((cubePosition.x - cubeSize.x / 2) + ballRadius))) {
            ballSpeed.x *= -1.0;
            ballSpeed.x *= 0.9;
            ballPosition.x = (cubePosition.x - cubeSize.x / 2) + ballRadius;
        }
        if ((ballPosition.y <= ((cubePosition.y - cubeSize.y / 2) + ballRadius))) {
            ballSpeed.y *= -1.0;
            ballSpeed.y *= 0.9;
            ballPosition.y = (cubePosition.y - cubeSize.y / 2) + ballRadius;
        }
        if ((ballPosition.z <= ((cubePosition.z - cubeSize.z / 2) + ballRadius))) {
            ballSpeed.z *= -1.0;
            ballSpeed.z *= 0.9;
            ballPosition.z = (cubePosition.z - cubeSize.z / 2) + ballRadius;
        }
        //---------------------------------------------------------------------------------
        if ((ballPosition.x >= ((cubePosition.x + cubeSize.x / 2) - ballRadius))) {
            ballSpeed.x *= -1.0;
            ballSpeed.x *= 0.9;
            ballPosition.x = (cubePosition.x + cubeSize.x / 2) - ballRadius;
        }
        if ((ballPosition.y >= ((cubePosition.y + cubeSize.y / 2) - ballRadius))) {
            ballSpeed.y *= -1.0;
            ballSpeed.y *= 0.9;
            ballPosition.y = (cubePosition.y + cubeSize.y / 2) - ballRadius;
        }
        if ((ballPosition.z >= ((cubePosition.z + cubeSize.z / 2) - ballRadius))) {
            ballSpeed.z *= -1.0;
            ballSpeed.z *= 0.9;
            ballPosition.z = (cubePosition.z + cubeSize.z / 2) - ballRadius;
        }

        //------------------------------BALL1---------------------------------------------------
        ballSpeed1.x += (GetFrameTime() * gravity.x);
        ballSpeed1.y += (GetFrameTime() * gravity.y);
        ballSpeed1.z += (GetFrameTime() * gravity.z);
        ballPosition1.x += GetFrameTime() * ballSpeed1.x;
        ballPosition1.y += GetFrameTime() * ballSpeed1.y;
        ballPosition1.z += GetFrameTime() * ballSpeed1.z;
        //---------------------------------------------------------------------------------
        if ((ballPosition1.x <= ((cubePosition.x - cubeSize.x / 2) + ballRadius))) {
            ballSpeed1.x *= -1.0;
            ballPosition1.x = (cubePosition.x - cubeSize.x / 2) + ballRadius;
        }
        if ((ballPosition1.y <= ((cubePosition.y - cubeSize.y / 2) + ballRadius))) {
            ballSpeed1.y *= -1.0;
            ballPosition1.y = (cubePosition.y - cubeSize.y / 2) + ballRadius;
        }
        if ((ballPosition1.z <= ((cubePosition.z - cubeSize.z / 2) + ballRadius))) {
            ballSpeed1.z *= -1.0;
            ballPosition1.z = (cubePosition.z - cubeSize.z / 2) + ballRadius;
        }
        //---------------------------------------------------------------------------------
        if ((ballPosition1.x >= ((cubePosition.x + cubeSize.x / 2) - ballRadius))) {
            ballSpeed1.x *= -1.0;
            ballPosition1.x = (cubePosition.x + cubeSize.x / 2) - ballRadius;
        }
        if ((ballPosition1.y >= ((cubePosition.y + cubeSize.y / 2) - ballRadius))) {
            ballSpeed1.y *= -1.0;
            ballPosition1.y = (cubePosition.y + cubeSize.y / 2) - ballRadius;
        }
        if ((ballPosition1.z >= ((cubePosition.z + cubeSize.z / 2) - ballRadius))) {
            ballSpeed1.z *= -1.0;
            ballPosition1.z = (cubePosition.z + cubeSize.z / 2) - ballRadius;
        }
       
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                //DrawGrid(10, 1.0f);                
                DrawCubeWiresV(cubePosition, cubeSize, BLUE);
                DrawSphere(ballPosition, ballRadius, RED); 
                DrawSphere(ballPosition1, ballRadius, GREEN);
                
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}