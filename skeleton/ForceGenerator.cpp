#include "ForceGenerator.h"
#include "Particle.hpp"

ForceGenerator::ForceGenerator(Vector3 force) : force(force), time(.0)
{
}

ForceGenerator::~ForceGenerator() {}

void 
ForceGenerator::applyForce(Particle* particle) const {
	particle->addForce(force);
}

void 
ForceGenerator::setForce(Vector3 newForce) {
	force = newForce;
}

void 
ForceGenerator::update(double dt) {
	time += dt;
}
