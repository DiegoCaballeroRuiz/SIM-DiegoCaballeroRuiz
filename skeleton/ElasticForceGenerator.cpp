#include "ElasticForceGenerator.h"

#include "Particle.hpp"

ElasticForceGenerator::ElasticForceGenerator(double k, double restingLength) 
	: SpringForceGenerator(k, restingLength)
{
}

void 
ElasticForceGenerator::applyForce(Particle* particle) {
	if (!anchors.count(particle)) return;

	Vector3 distance = particle->getTransform()->p - anchors[particle]->getTransform()->p;
	double distanceMagnitude = distance.magnitude();
	Vector3 direction = distance.getNormalized();

	double deltaX = distanceMagnitude - restingLength;
	if (deltaX < 0) return;

	Vector3 force = -k * deltaX * direction;

	particle->addForce(force);
}
