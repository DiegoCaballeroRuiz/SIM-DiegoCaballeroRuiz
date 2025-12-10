#include "SpringForceGenerator.h"

#include "Particle.hpp"

SpringForceGenerator::SpringForceGenerator(double k, double restingLength) 
	: ForceGenerator(), anchors(), k(k), restingLength(restingLength)
{
}

SpringForceGenerator::~SpringForceGenerator() {}


void 
SpringForceGenerator::applyForce(GameObject* gObject)  {
	if (!anchors.count(gObject)) return;

	Vector3 distance = gObject->getTransform()->p - anchors[gObject]->getTransform()->p;
	double distanceMagnitude = distance.magnitude();
	Vector3 direction = distance.getNormalized();

	Vector3 force = -k * (distanceMagnitude - restingLength) * direction;

	gObject->addForce(force);
}


void 
SpringForceGenerator::attachParticle(GameObject* affected, GameObject* anchor) {
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