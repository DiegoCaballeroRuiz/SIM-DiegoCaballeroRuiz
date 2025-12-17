#pragma once

#include "ForceGenerator.h"
class FrictionForceGenerator : public ForceGenerator
{
	double coefficient;
public:
	FrictionForceGenerator(double coefficient);
	~FrictionForceGenerator() {}

	void applyForce(GameObject* gObject) override;
};

