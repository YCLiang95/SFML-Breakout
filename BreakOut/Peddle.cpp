#include "Peddle.h"
#include "GameManager.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include<iostream>

void Peddle::Update() {

	sf::Vector2i localPosition = sf::Mouse::getPosition(GameManager::getInstance()->window);
	float d = abs(lastMousePosition.x - localPosition.x) + abs(lastMousePosition.y - localPosition.y);
	lastMousePosition = localPosition;


	//keyboard control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		mouseControl = false;
		y -= speedY * GameManager::getInstance()->deltaTime;
		if (y < 0) y = 0;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		mouseControl = false;
		y += speedY * GameManager::getInstance()->deltaTime;
		if (y + 100 > GameManager::getInstance()->height)
			y = GameManager::getInstance()->height - 100;
	} else if (d > 1.0f)
		mouseControl = true;

	//mouse control
	if (mouseControl) {
		localPosition.y = localPosition.y - 50;
		if (localPosition.y < 0) localPosition.y = 0;
		if (localPosition.y + 100 > GameManager::getInstance()->height) localPosition.y = GameManager::getInstance()->height - 100;

		if (y > localPosition.y)
			y -= std::max(speedY, y - localPosition.y) * GameManager::getInstance()->deltaTime;
		else
			y += std::max(speedY, localPosition.y - y) * GameManager::getInstance()->deltaTime;
	}

	ParticleSystem::getInstance()->Add(new Particle(x, y + 50, sf::Color::Red, 0.2f));

	int t = (int)y;
  	for (int i = 0; i < 100; i++) {
		if (t + i < GameManager::getInstance()->height)
			if (x < GameManager::getInstance()->width / 2)
				GameManager::getInstance()->left[t + i] = true;
			else
				GameManager::getInstance()->right[t + i] = true;
	}

}

void Peddle::Draw() {
	shape.setPosition(x, y);
	GameManager::getInstance()->window.draw(shape);
}

Peddle::Peddle(float x, float y) {
	this->x = x;
	this->y = y;

	mouseControl = false;

	speedX = 0.0f;
	speedY = 250.0f;

	shape.setSize(sf::Vector2f(10, 100));
	shape.setFillColor(sf::Color(255, 0, 0));
}