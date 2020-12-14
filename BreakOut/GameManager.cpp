#include "GameManager.h"
#include <iostream>

GameManager* GameManager::instance;

void GameManager::Update() {

    if (!isRunning) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            isRunning = true;
            life = 3;

            bricks.clear();

            bricksCount = 0;
            for (int i = 0; i < 14; i++)
                for (int j = 0; j < 5; j++) {
                    if (rand() % 100 > 50) {
                        bricks.push_back(new Brick(40.0f + i * 52, 100.0f + j * 12));
                        if (!bricks[bricks.size() - 1]->isInvincible)
                            bricksCount++;
                    }
                }

            ball->Reset();
            timeScale = 1.0f;
        }
    }
    else if (life <= 0) {
        isRunning = false;
        winningText.setString("You! Press Enter to Play Again!");
    } else if (bricksCount <= 0){
        isRunning = false;
        winningText.setString("You Won! Press Enter to Play Again!");

        victorySound.play();
    }

    if (!plusPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
        plusPressed = true;
        timeScale *= 2;
    }

    if (plusPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        plusPressed = false;

    deltaTime = (float)(clock() - lastTime) / CLOCKS_PER_SEC * timeScale;
    lastTime = clock();

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window.close();
            gameOver = true;
        }
    }

    peddle->Update();

    ball->Update();

    ps->Update();

    Draw();
}

void GameManager::Draw() {
    window.clear();
    ball->Draw();

    scoreTextLeft.setString("Life: " + std::to_string(life));
    scoreTextRight.setString(std::to_string(bricksCount) + " bricks remain");
    window.draw(scoreTextLeft);
    window.draw(scoreTextRight);

    if (!isRunning)
        window.draw(winningText);

    peddle->Draw();

    ps->Draw();

    for (int i = 0; i < bricks.size(); i++)
        bricks[i]->Draw();

    window.display();
}

GameManager* GameManager::getInstance(){
    if (!instance)
        instance = new GameManager;
    return instance;
}

void GameManager::LoadFont() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Failed to load Font" << std::endl;
        return;
    }


    scoreTextLeft.setFont(font);
    scoreTextRight.setFont(font);
    scoreTextLeft.setCharacterSize(24);
    scoreTextRight.setCharacterSize(24);
    scoreTextLeft.setFillColor(sf::Color::White);
    scoreTextRight.setFillColor(sf::Color::White);
    scoreTextRight.setPosition(width - 100, 0);

    winningText.setFont(font);
    winningText.setFillColor(sf::Color::White);
    winningText.setPosition(300.0f, 500.0f);
    winningText.setString("Press Enter to Start");
}