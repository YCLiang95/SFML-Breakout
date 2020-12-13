#pragma once
#include <SFML/Graphics.hpp>

class Particle {
public:
	float lifespan;
	float timeSinceCreated;

	float x, y;
	float speedx, speedy;

	bool isDead;

	sf::CircleShape shape;

	Particle(float x, float y, sf::Color color, float lifespan = 3.0f) {
		this->x = x;
		this->y = y;
		this->lifespan = lifespan;
		timeSinceCreated = 0.0f;
		speedx = rand() % 100 + 100;
		speedy = rand() % 100 + 100;
		if (rand() % 2 == 0) speedx *= -1;
		if (rand() % 2 == 0) speedy *= -1;
		isDead = false;

		shape.setRadius(5);
		shape.setFillColor(color);
	}

	void Update();
	void Draw();
};