#ifndef DEF_BALL
#define DEF_BALL

#include "raylib.h"

typedef struct Ball {
    int radius;
    Vector2 position;
    Vector2 speed;
    Color color;
    bool drag;
} Ball;

void checkMouseBallCollision(Vector2 mouse, Ball *ball, float deltaTime);
void checkBallWallCollision(Ball *ball);
void checkBallBallCollision(Ball *b1, Ball *b2);
   // int ballRadius = 20.0f;
   // Vector2 ballPosition = { 50.0f, 50.0f };
   // Vector2 ballSpeed = { 5.0f, 4.0f };
   // Color ballColor = DARKBLUE;
   // bool dragBall = false;

#endif
