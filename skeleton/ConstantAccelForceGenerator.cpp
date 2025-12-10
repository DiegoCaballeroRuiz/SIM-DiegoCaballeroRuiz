#include "ConstantAccelForceGenerator.h"

#include "GameObject.h"

ConstantAccelForceGenerator::ConstantAccelForceGenerator(double targetAccel, Vector3 direction) 
	: ForceGenerator(), targetAccel(targetAccel), direction(direction)
{
}

void 
ConstantAccelForceGenerator::applyForce(GameObject* gObject) {
	Vector3 forceToApply = gObject->getMass() * targetAccel * direction;
	gObject->addForce(forceToApply);
}

double
ConstantAccelForceGenerator::getTargetAccel() const {
	return targetAccel;
}

void 
ConstantAccelForceGenerator::setTargetAccel(double newTargetAccel) {
	targetAccel = newTargetAccel;
}

Vector3 
ConstantAccelForceGenerator::getDirection() const {
	return direction;
}

void 
ConstantAccelForceGenerator::setDirection(Vector3 newDir) {
	direction = newDir;
}
