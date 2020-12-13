#pragma once
#include <SFML/Graphics.hpp>

class Peddle {
public:
	float x, y;
	float speedX, speedY;

	sf::RectangleShape shape;

	sf::Vector2i lastMousePosition;

	bool mouseControl;

public:
	Peddle(float x, float y);

	void Update();
	void Draw();
};