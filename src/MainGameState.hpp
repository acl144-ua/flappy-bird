#pragma once
#include <GameState.hpp>
#include <GameOverState.hpp>
#include <deque>

extern "C" {
    #include <raylib.h>
}

struct Bird { float x, y; float vy; };

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

        static const int RADIUS = 17;
        static constexpr float GRAVEDAD = 400.0f;
        static const int PIPE_GAP = 150;
        static const int PIPE_WIDTH = 60;
        static constexpr float PIPE_SPEED = 200.0f;
        static const int PIPE_W = 32;
        static const int PIPE_H = 320;
};