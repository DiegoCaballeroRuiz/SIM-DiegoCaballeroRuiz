#include "ForceGenerator.h"
#include "Particle.hpp"

ForceGenerator::ForceGenerator(Vector3 force, Vector3 pos) : force(force), position(pos), time(.0)
{
}

ForceGenerator::~ForceGenerator() {}

void 
ForceGenerator::applyForce(Particle* particle) {
	particle->addForce(force);
}

void 
ForceGenerator::applyForce(physx::PxRigidBody* solid) {
	solid->addForce(force);
}


void 
ForceGenerator::setForce(Vector3 newForce) {
	force = newForce;
}

void 
ForceGenerator::update(double dt) {
	time += dt;
}
