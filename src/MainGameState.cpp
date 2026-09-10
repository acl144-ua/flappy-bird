#include <MainGameState.hpp>
#include <iostream>

extern "C" {
    #include <raylib.h>
}

const float gravedad = 980.0f;

MainGameState::MainGameState() : player{200, 200, 0}
{
    
}

void MainGameState::init()
{

}

void MainGameState::handleInput()
{
    if (IsKeyPressed(KEY_SPACE)) 
        player.vy += -300;
}

void MainGameState::update(float deltaTime)
{
    player.vy += gravedad * deltaTime;
    player.y += player.vy * deltaTime;
    player.vy = 0;
}

void MainGameState::render()
{
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText("Bienvenido a Flappy Bird DCA.", 10, 10, 20, BLACK);
    EndDrawing();
    
    DrawCircle(200, 200, 17, RED);
}