#pragma once
#include <GameState.hpp>
#include <GameOverState.hpp>
#include <deque>

extern "C" {
    #include <raylib.h>
}

struct Bird { float x, y; float vy; float height, width; };

struct PipePair { Rectangle top, bot; bool scored = false; };

class MainGameState : public GameState
{
    public:
        MainGameState();
        ~MainGameState() = default;

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        char entered_key;
        Bird player;
        std::deque<PipePair> pipes;
        float spawnTimer;
        float spawnEvery = 1.5f;
        Rectangle boundingBox;
        int score = 0;
        Texture2D birdSprite;
        Texture2D pipeSprite;
        Sound jumpSound;
        Sound scoreSound;
        Sound hitSound;
        Sound dieSound;

        int RADIUS = 17;
        float GRAVEDAD = 400.0f;
        float PIPE_GAP;
        float PIPE_SPEED = 200.0f;
        int PIPE_W;
        int PIPE_H;

        static constexpr float EXTRA_H = 4.5;
};