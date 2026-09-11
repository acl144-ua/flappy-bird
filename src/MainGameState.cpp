#include <MainGameState.hpp>
#include <iostream>
#include "StateMachine.hpp"

MainGameState::MainGameState() : player{200, 200, 0}
{
    
}

void MainGameState::init()
{
    birdFrames.push_back(LoadTexture("assets/bluebird-downflap.png"));
    birdFrames.push_back(LoadTexture("assets/bluebird-midflap.png"));
    birdFrames.push_back(LoadTexture("assets/bluebird-upflap.png"));
    //birdSprite = LoadTexture("assets/bluebird-midflap.png");
    pipeSprite = LoadTexture("assets/pipe-green.png");

    player.width = birdFrames[0].width;
    player.height = birdFrames[0].height;

    PIPE_W = pipeSprite.width;
    PIPE_H = pipeSprite.height;

    PIPE_GAP = player.height + EXTRA_H;

    jumpSound = LoadSound("audio/wing.wav");
    scoreSound = LoadSound("audio/point.wav");
    dieSound = LoadSound("audio/die.wav");
    hitSound = LoadSound("audio/hit.wav");

    for (int i = 0; i < 10; i++)
    {
        digitSprites.push_back(LoadTexture(("assets/" + std::to_string(i) + ".png").c_str()));
    }
}

void MainGameState::handleInput()
{
    if (IsKeyPressed(KEY_SPACE)) 
    {
        player.vy += -300;
        PlaySound(jumpSound);
    }
}

void MainGameState::update(float deltaTime)
{
    player.vy += GRAVEDAD * deltaTime;
    player.y += player.vy * deltaTime;
    player.vy = 0;

    //boundingBox = { player.x-RADIUS, player.y-RADIUS, RADIUS, RADIUS };
    boundingBox = { player.x - player.width/2, player.y - player.height/2, player.width, player.height };

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
            PlaySound(hitSound);
            PlaySound(dieSound);
            this->state_machine->add_state(std::make_unique<GameOverState>(score), true);
            score = 0;
        }

        if ((pipe.top.x + PIPE_W < player.x) && !pipe.scored)
        {
            score++;
            PlaySound(scoreSound);
            PIPE_GAP -= 0.1;
            PIPE_SPEED += 1;
            pipe.scored = true;
        }
    }

    // Delete pipes out of screen
    if (!pipes.empty() && pipes.front().top.x + PIPE_W < 0)
    {
        pipes.pop_front();
    }

    // Bird frames control
    frameTimer += deltaTime;
    if (frameTimer >= 0.1f)
    {
        frameTimer = 0;
        currentFrame = (currentFrame + 1) % 3;
    }
}

void MainGameState::render()
{
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText("Bienvenido a Flappy Bird DCA.", 10, 10, 20, BLACK);

    for (const auto& pipe : pipes)
    {
        DrawTextureEx(this->pipeSprite, {pipe.top.x + PIPE_W, pipe.top.y + PIPE_H}, 180.f, 1.0f, WHITE);
        DrawTextureEx(this->pipeSprite, {pipe.bot.x , pipe.bot.y}, 0.f, 1.0f, WHITE);
    }

    //int textWidth = MeasureText(std::to_string(score).c_str(), 40);
    //int posX = (GetScreenWidth() - textWidth) / 2;
    //DrawText(std::to_string(score).c_str(), posX, 30, 40, BLACK);
    std::string scoreStr = std::to_string(score);

    // Calculate total width
    int totalWidth = 0;
    for (char c : scoreStr)
    {
        int digit = c - '0';
        totalWidth += digitSprites[digit].width;
    }

    // Calculate posX to center score
    int posX = (GetScreenWidth() - totalWidth) / 2;
    int posY = 10;

    // Displaying digits without obstruction
    for (char c : scoreStr)
    {
        int digit = c - '0';
        DrawTexture(digitSprites[digit], posX, posY, WHITE);
        posX += digitSprites[digit].width;
    }

    //DrawCircle(player.x, player.y, RADIUS, RED);
    DrawTexture(birdFrames[currentFrame], player.x - player.width/2, player.y - player.height/2, WHITE);
    //DrawRectanglePro(boundingBox, {0,0}, 0, BLUE);

    EndDrawing();
}