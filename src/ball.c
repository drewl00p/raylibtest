#include "raylib.h"
#include "ball.h"
#include <math.h>
#define G 800

void checkMouseBallCollision(Vector2 mouse, Ball *ball, float deltaTime)
{
    if (CheckCollisionPointCircle(mouse, ball->position, ball->radius) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) ball->drag = true, ball->color=DARKGREEN;
    if (ball->drag) {
        ball->speed.x = (mouse.x - ball->position.x) / deltaTime / 2;
        ball->speed.y = (mouse.y - ball->position.y) / deltaTime / 2;
        ball->position = mouse;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            ball->drag = false;
            ball->color = DARKPURPLE;
        }
    } else {
        ball->position.x += ball->speed.x*deltaTime;
        ball->position.y += ball->speed.y*deltaTime;
        ball->speed.y += G*deltaTime;
    }
}

void checkBallWallCollision(Ball *ball)
{
    // Bounds Checking
    // Left wall
    if (ball->position.x > (GetScreenWidth()-ball->radius)) {
        ball->position.x = GetScreenWidth()-ball->radius;
        ball->speed.x *= -0.4f; // Bounce dampener
    }
    // Right wall
    if (ball->position.x < (ball->radius)) {
        ball->position.x = ball->radius;
        ball->speed.x *= -0.4f; // Bounce dampener
    }
    // Top wall 
    if (ball->position.y < (ball->radius)) {
        ball->position.y = ball->radius;
        ball->speed.y *= -0.4f; // Bounce dampener
    }
    // Bottom wall 
    if (ball->position.y > (GetScreenHeight()-ball->radius)) {
        ball->position.y = GetScreenHeight()-ball->radius;
        ball->speed.y *= -0.4f; // Bounce dampener
        ball->speed.x *= 0.6f; // Friction
    }
}
void checkBallBallCollision(Ball* b1, Ball* b2)
{
    if (CheckCollisionCircles(b1->position, b1->radius, b2->position, b2->radius)) {
        // calculate the collision normal
        float nx = b2->position.x - b1->position.x;
        float ny = b2->position.y - b1->position.y;
        float length = sqrtf(nx * nx + ny * ny);
        nx /= length;
        ny /= length;

        // calculate the relative velocity
        float dvx = b2->speed.x - b1->speed.x;
        float dvy = b2->speed.y - b1->speed.y;

        // calculate the dot product of the relative velocity and the collision normal
        float dot = dvx * nx + dvy * ny;

        // calculate the impulse
        float impulse = -2.0f * dot / (1.0f / b1->radius + 1.0f / b2->radius);

        // Apply the impulse to the balls' velocities
        b1->speed.x -= impulse * nx / b1->radius;
        b1->speed.y -= impulse * ny / b1->radius;
        b2->speed.x += impulse * nx / b2->radius;
        b2->speed.y += impulse * ny / b2->radius;

        // Separate the balls to prevent overlapping
        float overlap = b1->radius + b2->radius - length;
        b1->position.x -= nx * overlap * 0.5f;
        b1->position.y -= ny * overlap * 0.5f;
        b2->position.x += nx * overlap * 0.5f;
        b2->position.y += ny * overlap * 0.5f;
    }
}
