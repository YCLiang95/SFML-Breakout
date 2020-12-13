#include "ParticleSystem.h"

ParticleSystem* ParticleSystem::instance;

void ParticleSystem::Draw() {
	for (int i = 0; i < particles.size(); i++)
		particles[i]->Draw();
}

void ParticleSystem::Update() {
	for (vector<Particle*>::iterator it = particles.begin(); it != particles.end();) {
		(**it).Update();
		//Removed dead particals
		if ((**it).isDead) {
			it = particles.erase(it);
			//cout << "Partical Despawn!" << endl;
		}
		else {
			++it;
		}
	}
}

void ParticleSystem::Add(Particle* particle) {
	particles.push_back(particle);
}

ParticleSystem* ParticleSystem::getInstance() {
	if (!instance)
		instance = new ParticleSystem;
	return instance;
}