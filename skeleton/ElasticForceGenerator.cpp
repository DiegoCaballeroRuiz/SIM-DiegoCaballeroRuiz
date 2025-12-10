#include "ElasticForceGenerator.h"

#include "Particle.hpp"
#include "Solid.h"

ElasticForceGenerator::ElasticForceGenerator(double k, double restingLength) 
	: SpringForceGenerator(k, restingLength)
{
}

void 
ElasticForceGenerator::applyForce(GameObject* gObject) {
	if (!anchors.count(gObject)) return;
	
	Vector3 distance = gObject->getTransform()->p - anchors[gObject]->getTransform()->p;
	double distanceMagnitude = distance.magnitude();
	Vector3 direction = distance.getNormalized();

	double deltaX = distanceMagnitude - restingLength;
	if (deltaX < 0) return;

	Vector3 force = -k * deltaX * direction;

	gObject->addForce(force);
}

