#pragma once

#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

class Particle {
protected:
	Vector3 velocity, forceSum;
	physx::PxTransform pose;
	RenderItem* renderItem;
	double damping, invMass;

	double lifetime, timeAlive;

public:
	Particle(Vector3 pos, Vector3 vel, double damp, double mass, Vector4 color = {1.0, 1.0, 1.0, 1.0}, double lifeTime = 100.0);
	~Particle();
	
	void integrate(double t);
	physx::PxTransform* getTransform() { return &pose; }

	bool isAlive() { return timeAlive < lifetime; }

	void addForce(Vector3 force);
};