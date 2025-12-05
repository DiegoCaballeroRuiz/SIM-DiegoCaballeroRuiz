#pragma once

#include "ForceGenerator.h"

const double WATER_DENSITY = 1000;
const double GRAVITY_ACCEL = 9.8;
const double PARTICLE_HEIGHT = 1.0;

class FlotationForceGenerator : public ForceGenerator
{
	double gravity, density, particleHeightHalf, height, volume;
public:
	FlotationForceGenerator(double liquidHeight, double volume, Vector3 pos = {.0, .0, .0}, double liquidDensity = WATER_DENSITY, double gravity = GRAVITY_ACCEL, double pHeight = PARTICLE_HEIGHT);
	~FlotationForceGenerator();

	void applyForce(physx::PxRigidBody* solid) override;
	void applyForce(Particle* particle) override;
};