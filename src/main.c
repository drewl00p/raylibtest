/*******************************************************************************************
*
*  Intial testing using raylib.h
*  Throw a ball around with the mouse
*
********************************************************************************************/

#include "raylib.h"
#include "ball.h"
#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int numBalls = 3;
    //Ball ball = {.radius = 20.0f, .position = { 50.0f, 50.0f }, .speed = { 5.0f, 4.0f }, .color = DARKPURPLE, .drag = false};

    InitWindow(screenWidth, screenHeight, "ball throw");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------
    
    Ball** balls = calloc(numBalls, sizeof(Ball*));
    for(int i=0; i<numBalls; i++)
    {
        Ball* b = calloc(1, sizeof(Ball));
        if (b) {
            b->radius = 20.0f* (i+1);
            b->position = (Vector2){ 50.0f * (i+1), 50.0f };
            b->speed = (Vector2){ 5.0f, 4.0f };
            b->color = DARKPURPLE;
            b->drag = false;
        }
        balls[i] = b;
    }

    // Main game loop
    //---------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //---------------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();
        Vector2 mouse = GetMousePosition();
        
        for(int i=0; i<numBalls;i++) {
            checkMouseBallCollision(mouse, balls[i], deltaTime);
            checkBallWallCollision(balls[i]);
            for(int j = i+1; j<numBalls; j++) {
                checkBallBallCollision(balls[i], balls[j]);
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);
            for(int i=0; i<numBalls;i++) {
                DrawCircleV(balls[i]->position, balls[i]->radius, balls[i]->color);
                //fprintf(stdout,"delta: %f x:%f y:%f\n",deltaTime, balls[i]->speed.x, balls[i]->speed.y);
            }
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
