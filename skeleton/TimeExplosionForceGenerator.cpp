#include "TimeExplosionForceGenerator.h"

#include "Particle.hpp"
#include <cmath>

TimeExplosionForceGenerator::TimeExplosionForceGenerator(double forceMagnitude, double radius, double timeForActivation) 
	: ForceGenerator(Vector3(0.0)), radius(radius), activationTime(timeForActivation), forceMagnitude(forceMagnitude)
{
}

void 
TimeExplosionForceGenerator::applyForce(GameObject* gObject)  {
	Vector3 distance = gObject->getTransform()->p - position;
	double quadraticDistanceMagnitude = distance.magnitudeSquared();

	if (quadraticDistanceMagnitude > std::pow(radius, 2)) return;

	Vector3 force = distance * (forceMagnitude / quadraticDistanceMagnitude);
	force *= pow(exp(1.0), -(time / activationTime));
	gObject->addForce(force);
}
