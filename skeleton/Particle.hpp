#pragma once

#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

class Particle {
	Vector3 velocity, acceleration;
	physx::PxTransform pose;
	RenderItem* renderItem;

public:
	Particle(Vector3 pos, Vector3 vel, Vector3 accel);
	~Particle();
	
	void integrate(double t);
	
	void setAccel(Vector3 newAccel);
	Vector3 getAccel() const;
};