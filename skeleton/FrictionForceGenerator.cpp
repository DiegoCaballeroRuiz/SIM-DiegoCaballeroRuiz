#include "FrictionForceGenerator.h"

#include "GameObject.h"

FrictionForceGenerator::FrictionForceGenerator(double coefficient) 
	: ForceGenerator(), coefficient(coefficient)
{}

void 
FrictionForceGenerator::applyForce(GameObject* gObject) {
	Vector3 vel = gObject->getVelocity();
	gObject->addForce(-vel * coefficient);
}
