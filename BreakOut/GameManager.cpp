#include "GameManager.h"
#include <iostream>

GameManager* GameManager::instance;

void GameManager::Update() {

    if (!isRunning) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            isRunning = true;
            leftScore = 0;
            rightScore = 0;
            ball->Reset();
            //ball2->Reset();
            timeScale = 1.0f;
        }
    } else if (leftScore > 5 || rightScore > 5) {
        isRunning = false;
        if (leftScore > 5)
            winningText.setString("Left Won! Press Enter to Play Again!");
        else
            winningText.setString("Right Won! Press Enter to Play Again!");
        victorySound.play();
    }

    if (!plusPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        plusPressed = true;
        timeScale *= 2;
    }

    if (plusPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
   // ball2->Update();

    ps->Update();

    Draw();
}

void GameManager::Draw() {
    window.clear();
    ball->Draw();
    //ball2->Draw();

    scoreTextLeft.setString(std::to_string(leftScore));
    scoreTextRight.setString(std::to_string(rightScore));
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