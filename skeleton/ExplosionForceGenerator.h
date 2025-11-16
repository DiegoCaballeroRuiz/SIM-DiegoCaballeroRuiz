#pragma once

#include "ForceGenerator.h"


class ExplosionForceGenerator : public ForceGenerator
{
private:
	Vector3 position; 
	double radius;
public:
	ExplosionForceGenerator(Vector3 force, Vector3 position, double radius);
	~ExplosionForceGenerator() {}

	virtual void applyForce(Particle* particle);
};

