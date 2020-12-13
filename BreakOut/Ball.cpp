#include "Ball.h"
#include "GameManager.h"
#include <math.h>
#include <iostream>
#include "Particle.h"
#include "ParticleSystem.h"

Ball::Ball() {
	x = 400;
	y = 300;
	speedx = 400.0f;
	speedy = 300.0f;
	radius = 20.0f;
	shape.setRadius(20.0f);
	shape.setFillColor(sf::Color(255,255,255));
}

void Ball::Update() {

	if (!GameManager::getInstance()->isRunning)
		return;

	float  dx = x + speedx * GameManager::getInstance()->deltaTime;
	float dy = y + speedy * GameManager::getInstance()->deltaTime;

	if (dy < 0 || dy > GameManager::getInstance()->height - shape.getRadius() * 2) {
		speedy = -speedy;
		dy = std::max(dy, 1.0f);
		dy = std::min(GameManager::getInstance()->height - shape.getRadius() * 2, dy);
	}

	if (dx < 0 || dx > GameManager::getInstance()->width - shape.getRadius() * 2) {
		float a = dx - x;
		float b = dy - y;
		float m = 0;
		if (b == 0)
			m = 0;
		else
			m = a / b;

		if (dx < 0) {
			int c = (int)(dy + (0 - dx) * m);
			bool bounce = false;
			for (int i = 0; i < radius * 2; i++)
				if (c + i < GameManager::getInstance()->height && GameManager::getInstance()->left[c + i] == true)
					bounce = true;
			if (bounce){
				speedx = -speedx;
				dx = std::max(1.0f, dx);
				dx = std::min((float)GameManager::getInstance()->width - shape.getRadius() * 2, dx);
				for (int i = 0; i < 50; i++) {
					Particle* p = new Particle(x, y, sf::Color::Blue);
					GameManager::getInstance()->ps->Add(p);
				}
			} else {
				Reset(true);
				GameManager::getInstance()->rightScore += 1;
				dx = x;
				dy = y;
			}
		} else {
			int c = (int)(y + (dx + radius - GameManager::getInstance()->width) * m);
			bool bounce = false;
			for (int i = 0; i < radius * 2; i++)
				if (c + i < GameManager::getInstance()-> height && GameManager::getInstance()->right[c + i] == true)
					bounce = true;
			if (bounce) {
				speedx = -speedx;
				dx = std::max(1.0f, dx);
				dx = std::min((float)GameManager::getInstance()->width - shape.getRadius() * 2, dx);
				for (int i = 0; i < 50; i++) {
					Particle* p = new Particle(x, y, sf::Color::Blue);
					GameManager::getInstance()->ps->Add(p);
				}
			} else {
				Reset();
				GameManager::getInstance()->leftScore += 1;
				dx = x;
				dy = y;
			}
		}

	}

	ParticleSystem::getInstance()->Add(new Particle(x + radius / 2, y + radius / 2, sf::Color::Blue, 0.2f));

	x = dx;
	y = dy;
	shape.setPosition(x, y);
}

void Ball::Draw() {
	GameManager::getInstance()->window.draw(shape);
}

//Actually should be called hit
void Ball::Reset(bool left) {

	//Generate Particles
	for (int i = 0; i < 50; i++) {
		Particle* p = new Particle(x ,y, sf::Color::Green);
		GameManager::getInstance()->ps->Add(p);
	}

	GameManager::getInstance()->timeScale += 0.1f;

	x = GameManager::getInstance()->width / 2;
	y = GameManager::getInstance()->height / 2;
	speedx = GameManager::getInstance()->width / 6 + rand() % (GameManager::getInstance()->width / 6);
	speedy = GameManager::getInstance()->height / 6 + rand() % (GameManager::getInstance()->height / 6);
	if (rand() % 2 == 0)
		speedy *= -1;
	if (left) speedx *= -1;
	shape.setPosition(x, y);
}