/*******************************************************************************************
*
*  Intial testing using raylib.h
*  Throw a ball around with the mouse
*
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>
#define G 800

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "ball throw");

    int ballRadius = 20.0f;
    Vector2 ballPosition = { 50.0f, 50.0f };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    Color ballColor = DARKBLUE;
    bool dragBall = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------
    
    // Main game loop
    //---------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //---------------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();
        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointCircle(mouse, ballPosition, ballRadius) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) dragBall = true;
        if (dragBall)
        {
            ballSpeed.x = (mouse.x - ballPosition.x) / deltaTime / 2;
            ballSpeed.y = (mouse.y - ballPosition.y) / deltaTime / 2;
            ballPosition = mouse;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                dragBall= false;
            }
        } else 
        {
            ballPosition.x += ballSpeed.x*deltaTime;
            ballPosition.y += ballSpeed.y*deltaTime;
            ballSpeed.y += G*deltaTime;
        }

        // Bounds Checking
        // Left wall
        if (ballPosition.x >= (GetScreenWidth()-ballRadius)) {
            ballPosition.x = GetScreenWidth()-ballRadius;
            ballSpeed.x *= -0.4f; // Bounce dampener
        }
        // Right wall
        if (ballPosition.x <= (ballRadius)) {
            ballPosition.x = ballRadius;
            ballSpeed.x *= -0.4f; // Bounce dampener
        }
        // Top wall 
        if (ballPosition.y <= (ballRadius)) {
            ballPosition.y = ballRadius;
            ballSpeed.y *= -0.4f; // Bounce dampener
        }
        // Bottom wall 
        if (ballPosition.y >= (GetScreenHeight()-ballRadius)) {
            ballPosition.y = GetScreenHeight()-ballRadius;
            ballSpeed.y *= -0.4f; // Bounce dampener
            ballSpeed.x *= 0.6f; // Friction
        }
        //----------------------------------------------------------------------------------

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawCircleV(ballPosition, ballRadius, ballColor);

            //fprintf(stdout,"delta: %f x:%f y:%f\n",deltaTime, ballSpeed.x, ballSpeed.y);
            DrawText("throw ball with mouse", 10, 10, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
