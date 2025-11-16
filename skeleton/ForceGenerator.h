#pragma once

#include "RenderUtils.hpp"

class Particle;
class ForceGenerator
{
protected:
	Vector3 force;
	Vector3 position;

	double time;

public:
	ForceGenerator(Vector3 force = { 0.0, 0.0, 0.0 });
	~ForceGenerator();

	virtual void applyForce(Particle* particle);

	void update(double dt);
	void setForce(Vector3 force);
};

