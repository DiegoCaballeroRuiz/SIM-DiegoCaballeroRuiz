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
	ForceGenerator(Vector3 force = { 0.0, 0.0, 0.0 }, Vector3 position = {.0, .0, .0});
	~ForceGenerator();

	virtual void applyForce(Particle* particle);

	void update(double dt);
	void setForce(Vector3 force);

	inline Vector3 getPosition() { return position; }
	inline void setPosition(const Vector3& newPos) { position = newPos; }
};

