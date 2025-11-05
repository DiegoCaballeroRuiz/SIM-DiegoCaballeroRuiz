#pragma once

#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

class Particle {
protected:
	Vector3 velocity, forceSum;
	physx::PxTransform pose;
	RenderItem* renderItem;
	double damping, invMass, mass;

	double lifetime, timeAlive;
	bool markedDead = false;

public:
	Particle(Vector3 pos, Vector3 vel, double damp, double mass, Vector4 color = {1.0, 1.0, 1.0, 1.0}, double lifeTime = 100.0);
	~Particle();
	
	void integrate(double t);
	physx::PxTransform* getTransform() { return &pose; }

	bool isAlive() const { return markedDead || timeAlive < lifetime; }
	void kill() { markedDead = true; }

	void addForce(Vector3 force);

	double getMass() const;

	void setStatic();
};