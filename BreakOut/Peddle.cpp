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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		mouseControl = false;
		x -= speedX * GameManager::getInstance()->deltaTime;
		if (x < 0) x = 0;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		mouseControl = false;
		x += speedX * GameManager::getInstance()->deltaTime;
		if (x + 100 > GameManager::getInstance()->width)
			x = GameManager::getInstance()->width - 100;
	} else if (d > 1.0f)
		mouseControl = true;

	//mouse control
	if (mouseControl) {
		localPosition.x = localPosition.x - 50;
		if (localPosition.x < 0) localPosition.x = 0;
		if (localPosition.x + 100 > GameManager::getInstance()->width) localPosition.x = GameManager::getInstance()->width - 100;

		if (x > localPosition.x)
			x -= std::max(speedX, x - localPosition.x) * GameManager::getInstance()->deltaTime;
		else
			x += std::max(speedX, localPosition.x - x) * GameManager::getInstance()->deltaTime;
	}

	//ParticleSystem::getInstance()->Add(new Particle(x, y + 50, sf::Color::Red, 0.2f));

	//std::cout << x << std::endl;
	int t = (int)x;
  	for (int i = 0; i < 100; i++) {
		if (t + i < GameManager::getInstance()->width)
				GameManager::getInstance()->peddleCollision[t + i] = true;

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

	speedX = 250.0f;
	speedY = 250.0f;

	shape.setSize(sf::Vector2f(100, 10));
	shape.setFillColor(sf::Color(255, 0, 0));
}