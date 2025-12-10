#pragma once

#include <random>
#include "core.hpp"
#include <vector>

class GameObject;
class Particle;
class ParticleGenerator
{
protected:
	Vector3 position, offset, direction;
	double duration, probGen, speed, mass;

	std::mt19937 mt;

	virtual Particle* genParticle() = 0;
public:
	ParticleGenerator(Vector3 positionOffset, Vector3 direction, double speed, double duration, double probGen, double mass);
	virtual ~ParticleGenerator() = 0;

	std::vector<GameObject*> generate(int nParticles);

	Vector3 getPos();
	void setPos(Vector3 newPos);

	Vector3 getOffset();
	void setOffset(Vector3 newOffset);

	Vector3 getVel();
	void setVel(Vector3 newVel);

	double getDuration();
	void setDuration(double newDuration);

	double getProbGen();
	void setProbGen(double newProb);

	double getSpeed();
	void setSpeed(double newSpeed);

	Vector3 getDirection();
	void setDirection(Vector3 newDir);
};

