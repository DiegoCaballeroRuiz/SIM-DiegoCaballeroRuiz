#pragma once
#include "Particle.hpp"

class Proyectile : public Particle
{
protected:
	Vector3 realVelocity;
	double realMass, targetMass;

	void setSimulatedMass();
public:
	Proyectile(Vector3 pos, Vector3 realVel, Vector3 targetVelocity, Vector3 accel, double damp, double mass, Vector4 color = {1.0, 1.0, 1.0, 1.0});
};

