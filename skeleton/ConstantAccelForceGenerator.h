#pragma once

#include "ForceGenerator.h"

class ConstantAccelForceGenerator : public ForceGenerator
{
	double targetAccel;
	Vector3 direction;
public:
	ConstantAccelForceGenerator(double targetAccel, Vector3 direction);
	~ConstantAccelForceGenerator() {}

	void applyForce(Particle* particle) const override;

	double getTargetAccel() const;
	void setTargetAccel(double targetAccel);

	Vector3 getDirection() const;
	void setDirection(Vector3 newDir);
};

