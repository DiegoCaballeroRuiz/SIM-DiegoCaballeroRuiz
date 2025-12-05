#pragma once

#include "SpringForceGenerator.h"

class ElasticForceGenerator : public SpringForceGenerator
{
public:
	ElasticForceGenerator(double k, double restingLength);
	void applyForce(physx::PxRigidBody* solid) override;
	void applyForce(Particle* particle) override;
};

