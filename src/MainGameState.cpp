#include <MainGameState.hpp>
#include <iostream>

extern "C" {
    #include <raylib.h>
}

MainGameState::MainGameState()
{
}

void MainGameState::init()
{

}

void MainGameState::handleInput()
{

}

void MainGameState::update(float deltaTime)
{

}

void MainGameState::render()
{
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText("Bienvenido a Flappy Bird DCA.", 10, 10, 20, BLACK);
    EndDrawing();
}