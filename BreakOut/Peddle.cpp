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

	//ParticleSystem::getInstance()->Add(new Particle(x + 50, y + 10, sf::Color::Blue, 0.2f));

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

bool Peddle::shouldCollide(float x, float y, float dx, float dy, float radius) {

	float a = dx - x;
	float b = dy - y;
	float m = 0;

	if (a == 0)
		m = 0;
	else
		m = b / a;

	float up = x + (dy - this->y) * m;

	if ((up >= this->x && up <= this->x + 100.0f && abs(y + m * (dx - x) - this->y) < radius))
		return true;
	else
		return false;
}