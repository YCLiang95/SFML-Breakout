#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
	float x, y;
	float height, width;

	bool isAlive;

	sf::Texture texture;
	sf::Sprite sprite;

	sf::RectangleShape shape;

	bool isInvincible;

	Brick(float x, float y);

	int shouldCollide(float x, float y, float dx, float dy, float radius);

	void Draw();
};