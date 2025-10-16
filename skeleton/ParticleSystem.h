#pragma once
#include <vector>

class Particle;
class ParticleGenerator;
class ParticleSystem
{
	struct genInfo {
		ParticleGenerator* generator;
		int nParticles;
	};
protected:
	std::vector<Particle*> particles;
	std::vector<genInfo> generators;

public:
	ParticleSystem();
	~ParticleSystem();

	void registerParticleGenerator(ParticleGenerator* gen, int nParticles);
	void update(double delta);
};

