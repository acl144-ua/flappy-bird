#include "GameOverState.hpp"
#include <iostream>
#include "StateMachine.hpp"
#include "MainGameState.hpp"

void GameOverState::init(){}

void GameOverState::handleInput()
{
    if(IsKeyPressed(KEY_SPACE)) {
        this->state_machine->add_state(std::make_unique<MainGameState>(), true);
    }
}

void GameOverState::update(float deltaTime){}

void GameOverState::render() 
{
    BeginDrawing();
    ClearBackground(WHITE);

    int fontSize = 40;
    int textWidth = MeasureText("Game Over", fontSize);
    int posX = (GetScreenWidth() - textWidth) / 2;
    int posY = (GetScreenHeight() - fontSize) / 2;
    DrawText("Game Over", posX, posY, fontSize, RED);

    EndDrawing();
}

void GameOverState::pause(){}

void GameOverState::resume(){}