#pragma once

#include "ForceGenerator.h"

class StrikeForceGenerator : public ForceGenerator
{
protected:
	double force, radius;
	Vector3 axis;
public:
	StrikeForceGenerator(double force, Vector3 axis, double radius);
	~StrikeForceGenerator() {}

	void applyForce(GameObject* gObject) override;
};

