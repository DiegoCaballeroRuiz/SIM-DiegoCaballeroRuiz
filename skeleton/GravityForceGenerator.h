#pragma once
#include "ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator
{
	double gravityAccel;
public:
	GravityForceGenerator(double gravityAccel);
	~GravityForceGenerator();

	virtual void applyForce(Particle* particle) const;
};

