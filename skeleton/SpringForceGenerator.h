#pragma once

#include "ForceGenerator.h"
#include <unordered_map>

class SpringForceGenerator : public ForceGenerator {	
protected:
	double k;
	double restingLength;
	std::unordered_map<Particle*, Particle*> anchors;
public:
	SpringForceGenerator(double k, double restingLength);
	~SpringForceGenerator();

	virtual void applyForce(Particle* particle) override;
	void attachParticle(Particle* affected, Particle* anchor);
	void setK(double k);
	double getK() const;
};

