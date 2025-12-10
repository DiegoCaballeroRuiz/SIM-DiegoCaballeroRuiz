#pragma once

#include "ForceGenerator.h"


class TimeExplosionForceGenerator : public ForceGenerator
{
	double activationTime, radius, forceMagnitude;
public:
	TimeExplosionForceGenerator(double forceMagnitude, double radius, double activationTime);
	~TimeExplosionForceGenerator() {}

	void applyForce(GameObject* gObject) override;
};

