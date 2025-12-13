#pragma once
#include <vector>

#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

class Particle;
class ParticleGenerator;
class ForceGenerator;
class SolidGenerator;
class GameObject;

class ParticleSystem
{
protected:
	struct pGenInfo {
		ParticleGenerator* generator;
		int nParticles;
	};

	struct sGenInfo {
		SolidGenerator* generator;
		int nSolids;
	};
	std::vector<GameObject*> gObjects;
	std::vector<pGenInfo> particleGenerators;
	std::vector<sGenInfo> solidGenerators;
	std::vector<ForceGenerator*> forceGenerators;

	int maxParticles;
	bool uncappedParticles;

	Vector3 pos;
	double range;
	bool uncappedRange;

	physx::PxScene* gScene;

public:
	ParticleSystem(Vector3 pos);
	ParticleSystem(Vector3 pos, int maxParticles);
	ParticleSystem(Vector3 pos, int maxParticles, double range);
	ParticleSystem(Vector3 pos, double range);

	~ParticleSystem();

	void registerParticleGenerator(ParticleGenerator* gen, int nParticles);
	/// NO LO BORRA !!!!!!!!!!!!!!!!
	void deRegisterParticleGenerator(ParticleGenerator* gen);

	void registerSolidGenerator(SolidGenerator* gen, int nParticles);
	/// NO LO BORRA !!!!!!!!!!!!!!!!
	void deRegisterSolidGenerator(SolidGenerator* gen);

	void registerForceGenerator(ForceGenerator* gen);
	/// NO LO BORRA !!!!!!!!!!!!!!!!
	void deRegisterForceGenerator(ForceGenerator* gen);

	virtual void update(double delta);

	inline std::vector<GameObject*>& getObjects() { return gObjects; }

	Vector3 getPosition() const;
	void setPosition(Vector3 newPos);
};

