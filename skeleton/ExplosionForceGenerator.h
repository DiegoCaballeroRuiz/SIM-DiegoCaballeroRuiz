#pragma once

#include "ForceGenerator.h"


class ExplosionForceGenerator : public ForceGenerator
{
private:
	double radius;
public:
	ExplosionForceGenerator(Vector3 force, Vector3 position, double radius);
	~ExplosionForceGenerator() {}

	void applyForce(physx::PxRigidBody* solid) override;
	virtual void applyForce(Particle* particle);
};

