#pragma once

#include "GameObject.h"

class Particle : public GameObject {
protected:
	Vector3 velocity, forceSum;

	double damping, invMass, mass;

public:
	Particle(Vector3 pos, Vector3 vel, double damp, double mass, Vector4 color = {1.0, 1.0, 1.0, 1.0}, double lifeTime = 100.0);
	~Particle();
	
	virtual void integrate(double t) override;

	void addForce(Vector3 force) override;

	inline double getMass() const override { return mass; }
	virtual void setMass(double newMass) override;

	void setStatic();
};