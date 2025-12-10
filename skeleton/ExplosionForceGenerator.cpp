#include "ExplosionForceGenerator.h"

#include "Particle.hpp"
#include "Solid.h"
#include <cmath>

ExplosionForceGenerator::ExplosionForceGenerator(Vector3 force, Vector3 pos, double radius) 
	: ForceGenerator(force, pos), radius(radius)
{
}

void 
ExplosionForceGenerator::applyForce(GameObject* gObject) {
	Vector3 distance = gObject->getTransform()->p - position;
	double quadraticDistanceMagnitude = distance.magnitudeSquared();

	if (quadraticDistanceMagnitude > std::pow(radius, 2)) return;

	double forceMagnitude = force.magnitude();
	float quadraticInverseDistance = 1 / quadraticDistanceMagnitude;

	gObject->addForce((distance * forceMagnitude) * quadraticInverseDistance);
}
