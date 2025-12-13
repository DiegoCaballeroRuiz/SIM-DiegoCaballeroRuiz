#include "StrikeForceGenerator.h"

#include "GameObject.h"
#include <cmath>

StrikeForceGenerator::StrikeForceGenerator(double force, Vector3 axis, double radius)
	: ForceGenerator(), force(force), axis(axis), radius(radius) 
{ 
}

void 
StrikeForceGenerator::applyForce(GameObject* gObject) {
	Vector3 distance = gObject->getTransform()->p - position;
	double distanceMagnitude = distance.magnitude();

	if (distanceMagnitude > radius) return;

	gObject->addForce(force * axis);
}
