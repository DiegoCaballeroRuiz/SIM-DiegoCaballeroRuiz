#pragma once

#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

class Particle {
	Vector3 velocity, acceleration;
	physx::PxTransform pose;
	RenderItem* renderItem;
	double damping;

public:
	Particle(Vector3 pos, Vector3 vel, Vector3 accel, double damp);
	~Particle();
	
	void integrate(double t);
	
	void setAccel(Vector3 newAccel) { acceleration = newAccel; }
	Vector3 getAccel() const { return acceleration; }
	physx::PxTransform* getTransform() { return &pose; }
};