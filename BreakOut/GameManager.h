#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Ball.h"
#include "Peddle.h"
#include "ParticleSystem.h"

class GameManager {
    GameManager() {
        width = 800;
        height = 600;
        window.create(sf::VideoMode(width, height), "Breakout");

        ball = new Ball();
        ball2 = new Ball();

        peddle = new Peddle(400, 580);

        peddleCollision = new bool[width];

        leftScore = 0.0f;
        rightScore = 0.0f;

        timeScale = 1.0f;

        lastTime = clock();
        deltaTime = 0;

        ps = ParticleSystem::getInstance();

        plusPressed = false;
        isRunning = false;

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
    Ball* ball2;
    Peddle* peddle;

    bool* peddleCollision;

    int leftScore;
    int rightScore;

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