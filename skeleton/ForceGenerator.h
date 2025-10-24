#pragma once

#include "RenderUtils.hpp"

class Particle;
class ForceGenerator
{
protected:
	Vector3 force;
	Vector3 position;

public:
	ForceGenerator(Vector3 force = { 0.0, 0.0, 0.0 });
	~ForceGenerator();

	virtual void applyForce(Particle* particle) const;
	void setForce(Vector3 force);
};

