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
	isLauched = false;
	radius = 10.0f;
	shape.setRadius(radius);
	shape.setFillColor(sf::Color(255,255,255));

	if (!bufferHitSound.loadFromFile("hit.wav")) {
		std::cout << "Failded to load hit sound" << std::endl;
	}

	if (!bufferLoseSound.loadFromFile("score.wav")) {
		std::cout << "Failded to load lose sound" << std::endl;
	}

	hitSound.setBuffer(bufferHitSound);
	loseSound.setBuffer(bufferLoseSound);

	if (!texture.loadFromFile("ball.png")) {
		std::cout << "Faild to load image" << std::endl;
		return;
	}
	sprite.setTexture(texture);
	sprite.setScale(0.15f, 0.15f);
}

void Ball::Update() {

	if (!isLauched) {
		x = GameManager::getInstance()->peddle->x + 50.0f - radius;
		y = GameManager::getInstance()->peddle->y - 15.0f - radius;
		shape.setPosition(x, y);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
			isLauched = true;
		else
			return;
	}

	if (!GameManager::getInstance()->isRunning)
		return;

	float  dx = x + speedx * GameManager::getInstance()->deltaTime;
	float dy = y + speedy * GameManager::getInstance()->deltaTime;

	if (dy < 0) {
		speedy = -speedy;
		dy = std::max(dy, 1.0f);
		loseSound.play();
	}

	if (GameManager::getInstance()->peddle->shouldCollide(x, y, dx, dy, radius)) {
		speedy = -speedy;
		dy = std::max(1.0f, dy);
		dy = std::min((float)GameManager::getInstance()->height - 20.0f - shape.getRadius() * 2, dy);
		for (int i = 0; i < 50; i++) {
			Particle* p = new Particle(x, y, sf::Color::Blue);
			GameManager::getInstance()->ps->Add(p);
		}
		hitSound.play();
	} else if (dy > GameManager::getInstance()->height){
		Reset();
		GameManager::getInstance()->life -= 1;
		dx = x;
		dy = y;
		loseSound.play();
	}


	if (dx < 0 || dx > GameManager::getInstance()->width - shape.getRadius() * 2) {
		speedx = -speedx;
		dx = std::max(dx, 1.0f);
		dx = std::min(GameManager::getInstance()->width - shape.getRadius() * 2 - 1.0f, dx);
		loseSound.play();
	}

	for (int i = 0; i < GameManager::getInstance()->bricks.size(); i++) {
		float k = GameManager::getInstance()->bricks[i]->shouldCollide(x, y, dx, dy, radius);
		if (k != 0) {
			if (k == 1)
				speedy = -speedy;
			else if (k == 2)
				speedx = -speedx;
			dx = x;
			dy = y;
			hitSound.play();
			if (!GameManager::getInstance()->bricks[i]->isInvincible) {
				GameManager::getInstance()->bricks[i]->isAlive = false;
				GameManager::getInstance()->bricksCount -= 1;
				for (int i = 0; i < 50; i++) {
					Particle* p = new Particle(x, y, sf::Color::Blue);
					GameManager::getInstance()->ps->Add(p);
				}
			}
			break;
		} 
	}

	ParticleSystem::getInstance()->Add(new Particle(x + radius / 2, y + radius / 2, sf::Color::Blue, 0.2f));

	x = dx;
	y = dy;
	//shape.setPosition(x, y);
}

void Ball::Draw() {
	shape.setPosition(x, y);
	sprite.setPosition(x, y);
	GameManager::getInstance()->window.draw(shape);
	GameManager::getInstance()->window.draw(sprite);
}

//Actually should be called hit
void Ball::Reset(bool left) {

	//Generate Particles
	for (int i = 0; i < 50; i++) {
		Particle* p = new Particle(x ,y, sf::Color::Green);
		GameManager::getInstance()->ps->Add(p);
	}

	isLauched = false;

	speedx = GameManager::getInstance()->width / 6 + rand() % (GameManager::getInstance()->width / 6);
	speedy = GameManager::getInstance()->height / 6 + rand() % (GameManager::getInstance()->height / 6);
	speedy *= -1;
	if (left) speedx *= -1;
	shape.setPosition(x, y);
}