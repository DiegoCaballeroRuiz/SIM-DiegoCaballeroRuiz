#pragma once
#include <vector>

#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

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

	int maxParticles;
	bool uncappedParticles;

	Vector3 pos;
	double range;
	bool uncappedRange;

public:
	ParticleSystem(Vector3 pos);
	ParticleSystem(Vector3 pos, int maxParticles);
	ParticleSystem(Vector3 pos, int maxParticles, double range);
	ParticleSystem(Vector3 pos, double range);

	~ParticleSystem();

	void registerParticleGenerator(ParticleGenerator* gen, int nParticles);
	/// NO LO BORRA !!!!!!!!!!!!!!!!
	void deRegisterParticleGenerator(ParticleGenerator* gen);

	void registerForceGenerator(ForceGenerator* gen);
	/// NO LO BORRA !!!!!!!!!!!!!!!!
	void deRegisterForceGenerator(ForceGenerator* gen);

	void update(double delta);

	std::vector<Particle*> getParticles();

	Vector3 getPosition() const;
};

