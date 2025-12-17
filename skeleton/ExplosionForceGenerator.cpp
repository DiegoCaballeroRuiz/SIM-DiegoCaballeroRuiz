#include "ExplosionForceGenerator.h"
#include "GameObject.h"
#include <cmath>

ExplosionForceGenerator::ExplosionForceGenerator(Vector3 force, Vector3 position, double radius)
	: ForceGenerator(force, position), radius(radius), forceMagnitude(force.magnitude())
{

}

void 
ExplosionForceGenerator::applyForce(GameObject* gObject) {
	Vector3 distance = gObject->getTransform()->p - position;

	if (distance.magnitude() > radius) return;

	gObject->addForce(forceMagnitude * distance / distance.magnitudeSquared() * std::exp(-time/duration));
}