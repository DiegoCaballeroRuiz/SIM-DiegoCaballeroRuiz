#include "StrikeForceGenerator.h"

#include "GameObject.h"
#include <cmath>

StrikeForceGenerator::StrikeForceGenerator(double force, Vector3 axis, double radius)
	: ForceGenerator(), force(force), axis(axis), radius(radius), smallRaidus(radius * .5)
{ 
}

StrikeForceGenerator::StrikeForceGenerator(double force, Vector3 axis, double radius, double smallRadius)
	: ForceGenerator(), force(force), axis(axis), radius(radius), smallRaidus(smallRadius)
{
}

void 
StrikeForceGenerator::applyForce(GameObject* gObject) {
	Vector3 distance = gObject->getTransform()->p - position;
	double distanceMagnitude = distance.magnitude();

	if (distanceMagnitude > radius) return;

	gObject->addForce(force * axis);
	gObject->addForce(force * Vector3{ .0, -.5, .0 });

	if (distanceMagnitude < smallRaidus) return;

	if (axis.x > 0) {
		int sign = distance.z < 0 ? -1 : 1;
		gObject->addForce(force * Vector3{ .0, .0, .20 } * sign);
	}
	else {
		int sign = distance.x < 0 ? 1 : -1;
		gObject->addForce(force * Vector3{ .20, .0, .0 } *sign);
	}
}
