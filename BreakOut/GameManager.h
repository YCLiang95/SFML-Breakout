#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Ball.h"
#include "Peddle.h"
#include "ParticleSystem.h"
#include "Brick.h"

class GameManager {
    GameManager() {
        width = 800;
        height = 600;
        window.create(sf::VideoMode(width, height), "Breakout");

        ball = new Ball();

        peddle = new Peddle(400, 580);

        life = 3;
        bricksCount = 42;

        timeScale = 1.0f;

        lastTime = clock();
        deltaTime = 0;

        for (int i = 0; i < 14; i ++)
            for (int j = 0; j < 3; j++) {
                bricks.push_back(new Brick(40.0f + i * 52, 100.0f + j * 12));
            }

        bricksCount = bricks.size();

        ps = ParticleSystem::getInstance();

        plusPressed = false;
        isRunning = true;

        if (!bufferVictorySound.loadFromFile("victory.wav")) {
            std::cout << "Failded to load victory sound" << std::endl;
        }

        if (!bufferBGM.loadFromFile("bgm.wav")) {
            std::cout << "Failded to load bgm sound" << std::endl;
        }

        victorySound.setBuffer(bufferVictorySound);

        bgmSound.setBuffer(bufferBGM);
        bgmSound.setLoop(true);
        bgmSound.setVolume(50);
        bgmSound.play();
    }



public:
    int height, width;
    sf::RenderWindow window;
    bool gameOver = false;

    static GameManager* getInstance();
    void Draw();
    void Update();
    void LoadFont();

    Ball* ball;

    Peddle* peddle;
    vector<Brick*> bricks;

    int life;
    int bricksCount;

    clock_t lastTime;
    float deltaTime;

    sf::Font font;
    sf::Text scoreTextLeft;
    sf::Text scoreTextRight;
    sf::Text winningText;

    sf::SoundBuffer bufferVictorySound;
    sf::SoundBuffer bufferBGM;
    sf::Sound victorySound;
    sf::Sound bgmSound;

    bool plusPressed;
    float timeScale;
    bool isRunning;

    ParticleSystem* ps;

    ~GameManager() {
        delete(ball);
        delete peddle;
    }

private:
    static GameManager* instance;
};