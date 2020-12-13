#include "Particle.h"
#include "GameManager.h"

void Particle::Draw() {
	GameManager::getInstance()->window.draw(shape);
}

void Particle::Update() {
	timeSinceCreated += GameManager::getInstance()->deltaTime;
	if (timeSinceCreated > lifespan) {
		isDead = true;
		return;
	}

	x += speedx * GameManager::getInstance()->deltaTime;
	y += speedy * GameManager::getInstance()->deltaTime;

	shape.setPosition(x , y);
}