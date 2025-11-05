#include "ExplosionForceGenerator.h"

#include "Particle.hpp"
#include <cmath>

ExplosionForceGenerator::ExplosionForceGenerator(Vector3 force, Vector3 pos, double radius) 
	: ForceGenerator(force), position(pos), radius(radius)
{
}

void 
ExplosionForceGenerator::applyForce(Particle* particle) const {
	Vector3 distance = particle->getTransform()->p - position;
	double quadraticDistanceMagnitude = distance.magnitudeSquared();

	if (quadraticDistanceMagnitude > std::pow(radius, 2)) return;

	double forceMagnitude = force.magnitude();
	float quadraticInverseDistance = 1 / quadraticDistanceMagnitude;

	particle->addForce((distance * forceMagnitude) * quadraticInverseDistance);
}