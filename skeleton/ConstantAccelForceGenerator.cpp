#include "ConstantAccelForceGenerator.h"

#include "Particle.hpp"

ConstantAccelForceGenerator::ConstantAccelForceGenerator(double targetAccel, Vector3 direction) 
	: ForceGenerator(), targetAccel(targetAccel), direction(direction)
{
}

void 
ConstantAccelForceGenerator::applyForce(Particle* particle) const {
	Vector3 forceToApply = particle->getMass() * targetAccel * direction;
	particle->addForce(forceToApply);
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
