#pragma once

#include "ForceGenerator.h"

class StrikeForceGenerator : public ForceGenerator
{
protected:
	double force, radius, smallRaidus;
	Vector3 axis;
public:
	StrikeForceGenerator(double force, Vector3 axis, double radius);
	StrikeForceGenerator(double force, Vector3 axis, double radius, double smallRadius);
	~StrikeForceGenerator() {}

	void applyForce(GameObject* gObject) override;
};

