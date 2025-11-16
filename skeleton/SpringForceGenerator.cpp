#include "SpringForceGenerator.h"

#include "Particle.hpp"

SpringForceGenerator::SpringForceGenerator(double k, double restingLength) 
	: ForceGenerator(), anchors(), k(k), restingLength(restingLength)
{
}

SpringForceGenerator::~SpringForceGenerator() {}


void 
SpringForceGenerator::applyForce(Particle* particle)  {
	if (!anchors.count(particle)) return;

	Vector3 distance = particle->getTransform()->p - anchors[particle]->getTransform()->p;
	double distanceMagnitude = distance.magnitude();
	Vector3 direction = distance.getNormalized();

	Vector3 force = -k * (distanceMagnitude - restingLength) * direction;

	particle->addForce(force);
}

void 
SpringForceGenerator::attachParticle(Particle* affected, Particle* anchor) {
	anchors[affected] = anchor;
}

void 
SpringForceGenerator::setK(double newK) {
	k = newK;
}

double 
SpringForceGenerator::getK() const {
	return k;
}