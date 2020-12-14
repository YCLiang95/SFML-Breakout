#include "Brick.h"
#include "GameManager.h"

Brick::Brick(float x, float y) {
	this->x = x;
	this->y = y;

	shape.setPosition(x, y);
	sprite.setPosition(x, y);
	height = 10;
	width = 50;
	isAlive = true;

	shape.setSize(sf::Vector2f(50, 10));
	shape.setFillColor(sf::Color(255, 0, 0));

	if (rand() % 100 > 80)
		isInvincible = true;
	else
		isInvincible = false;

	if (!texture.loadFromFile("brick.png")) {
		std::cout << "Faild to load image" << std::endl;
		return;
	}
	sprite.setTexture(texture);
	sprite.setScale(1.0f, 1.0f);
}

void Brick::Draw() {
	if (isAlive) {
		GameManager::getInstance()->window.draw(shape);
		if (isInvincible)
			GameManager::getInstance()->window.draw(sprite);
	}
}

int Brick::shouldCollide(float x, float y, float dx, float dy, float radius) {
	if (!isAlive)
		return 0;

	float a = dx - x;
	float b = dy - y;
	float m = 0;
	float n = 0;

	if (a == 0)
		m = 0;
	else
		m = b / a;

	if (b == 0)
		n = 0;
	else
		n = a / b;

	float up = x + (dy  - this->y)  * m;
	float button = x + (dy - (this->y + height)) * m;

	float left = y + (dx  - this->x) * n;
	float right = y + (dx  - (this->x + width)) * n;

	if ((up >= this->x && up <= this->x + width && abs(y + m * (dx - x) - this->y) < radius) || (button >= this->x && button <= this->x + width && abs(y + m * (dx - x) - this->y - height) < radius))
		return 1;
	else if (left >= this->y && left <= this->y + height && abs(x + n * (dy - y) - this->x) < radius || right >= this->y && right <= this->y + height && abs(x + n * (dy - y) - this->x - width) < radius)
		return 2;
	else
		return 0;
}