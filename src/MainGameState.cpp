#include <MainGameState.hpp>
#include <iostream>
#include "StateMachine.hpp"

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
    player.vy += GRAVEDAD * deltaTime;
    player.y += player.vy * deltaTime;
    player.vy = 0;

    boundingBox = { player.x-RADIUS, player.y-RADIUS, RADIUS, RADIUS };

    // Pipes spawn
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnEvery)
    {
        spawnTimer = 0;

        int pipe_y_offset_top = GetRandomValue(PIPE_H/2, GetScreenWidth()/2);

        PipePair pp;
        pp.top = { (float)GetScreenWidth(), (float)-pipe_y_offset_top, (float)PIPE_W, (float)PIPE_H };
        pp.bot = { (float)GetScreenWidth(), (float)(PIPE_H - pipe_y_offset_top) + GetRandomValue(PIPE_H/2, GetScreenWidth()/2), (float)PIPE_W, (float)PIPE_H };
        
        pipes.push_back(pp);
    }

    // Move pipes position
    for (auto& pipe : pipes)
    {
        pipe.top.x -= PIPE_SPEED * deltaTime;
        pipe.bot.x -= PIPE_SPEED * deltaTime;

        if (CheckCollisionRecs(pipe.top, boundingBox) || CheckCollisionRecs(pipe.bot, boundingBox))
        {
            this->state_machine->add_state(std::make_unique<GameOverState>(score), true);
        }

        if ((pipe.top.x + PIPE_W < player.x) && !pipe.scored)
        {
            score++;
            pipe.scored = true;
        }
    }

    // Delete pipes out of screen
    if (!pipes.empty() && pipes.front().top.x + PIPE_W < 0)
    {
        pipes.pop_front();
    }
}

void MainGameState::render()
{
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText("Bienvenido a Flappy Bird DCA.", 10, 10, 20, BLACK);

    for (const auto& pipe : pipes)
    {
        DrawRectangle(pipe.top.x, pipe.top.y, pipe.top.width, pipe.top.height, GREEN);
        DrawRectangle(pipe.bot.x, pipe.bot.y, pipe.bot.width, pipe.bot.height, GREEN);
    }

    int textWidth = MeasureText(std::to_string(score).c_str(), 40);
    int posX = (GetScreenWidth() - textWidth) / 2;
    DrawText(std::to_string(score).c_str(), posX, 30, 40, BLACK);

    DrawCircle(player.x, player.y, RADIUS, RED);
    //DrawRectanglePro(boundingBox, {0,0}, 0, BLUE);

    EndDrawing();
}