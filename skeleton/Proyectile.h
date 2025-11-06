#pragma once
#include "Particle.hpp"


class Proyectile : public Particle
{
protected:
	Vector3 realVelocity;
	double targetMass, invTargetMass;

	void setSimulatedMass();
public:
	Proyectile(Vector3 pos, Vector3 realVel, Vector3 targetVelocity, double damp, double mass, Vector4 color = {1.0, 1.0, 1.0, 1.0}, double lifeTime = 100.0);
	~Proyectile() {}
	void setMass(double newMass) override;

	void integrate(double t) override;
};

