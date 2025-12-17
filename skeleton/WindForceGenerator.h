#pragma once

#include "ForceGenerator.h"

class WindForceGenerator : public ForceGenerator
{
	Vector3 direction;
	double windSpeed, windStrength;
public:
	WindForceGenerator(Vector3 direction, double speed, double force);
	~WindForceGenerator() {}

	void applyForce(GameObject* gObject) override;
};

