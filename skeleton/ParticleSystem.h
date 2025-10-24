#pragma once
#include <vector>

class Particle;
class ParticleGenerator;
class ForceGenerator;

class ParticleSystem
{
	struct genInfo {
		ParticleGenerator* generator;
		int nParticles;
	};
protected:
	std::vector<Particle*> particles;
	std::vector<genInfo> particleGenerators;
	std::vector<ForceGenerator*> forceGenerators;

public:
	ParticleSystem();
	~ParticleSystem();

	void registerParticleGenerator(ParticleGenerator* gen, int nParticles);
	/// NO LO BORRA !!!!!!!!!!!!!!!!
	void deRegisterParticleGenerator(ParticleGenerator* gen);

	void registerForceGenerator(ForceGenerator* gen);
	/// NO LO BORRA !!!!!!!!!!!!!!!!
	void deRegisterForceGenerator(ForceGenerator* gen);


	void update(double delta);
};

