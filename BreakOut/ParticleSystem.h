#pragma once
#include <vector>
#include "Particle.h"

using std::vector;

class ParticleSystem {
public:
	static ParticleSystem* getInstance();

	void Draw();
	void Update();

	void Add(Particle* particle);

	vector<Particle*> particles;

private:
	static ParticleSystem* instance;
};
