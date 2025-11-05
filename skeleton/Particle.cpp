#include "Particle.hpp"

#include <cmath>

Particle::Particle(Vector3 pos, Vector3 vel, double damp, double mass, Vector4 color, double lifetime) 
	: velocity(vel), pose(pos), damping(damp), mass(mass), invMass(std::pow(mass, -1)), lifetime(lifetime), timeAlive(0.0), forceSum(0.0, 0.0, 0.0)
{
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, color);
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void
Particle::integrate(double t) {
	velocity += forceSum * invMass * t;
	pose.p += velocity * t;
	velocity *= std::pow(damping, t);	
	timeAlive += t;
	forceSum = Vector3(0.0);
}

void 
Particle::addForce(Vector3 force) {
	forceSum += force;
}

void 
Particle::setStatic() {
	invMass = 0.0;
}

double 
Particle::getMass() const {
	return mass;
}
