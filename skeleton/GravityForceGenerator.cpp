#include "GravityForceGenerator.h"

#include "Particle.hpp"

GravityForceGenerator::GravityForceGenerator(double gravityAccel) : ForceGenerator(), gravityAccel(gravityAccel)
{
}

GravityForceGenerator::~GravityForceGenerator() 
{
}

void 
GravityForceGenerator::applyForce(Particle* particle) const {
	Vector3 forceToApply = particle->getMass() * Vector3(.0, -gravityAccel, .0);
	particle->addForce(forceToApply);
}
