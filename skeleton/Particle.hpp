#pragma once

#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

class Particle {
	Vector3 velocity;
	physx::PxTransform pose;
	RenderItem* renderItem;

public:
	Particle(Vector3 pos, Vector3 vel);
	~Particle();

	void integrate(double t);
};