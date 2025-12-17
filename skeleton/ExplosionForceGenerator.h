#pragma once
#include "ForceGenerator.h"

class ExplosionForceGenerator : public ForceGenerator
{
private:
	double radius;
	double forceMagnitude;
	double duration = 5;
public:
	ExplosionForceGenerator(Vector3 force, Vector3 position, double radius);
	~ExplosionForceGenerator() {}

	void applyForce(GameObject* gObject) override;
};

