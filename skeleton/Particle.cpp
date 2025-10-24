#include "Particle.hpp"

#include <cmath>

Particle::Particle(Vector3 pos, Vector3 vel, double damp, double mass, Vector4 color, double lifetime) 
	: velocity(vel), pose(pos), damping(damp), invMass(1/mass), lifetime(lifetime), timeAlive(0.0)
{
	const physx::PxSphereGeometry geo = physx::PxSphereGeometry(1.0);
	physx::PxShape* centreShape = CreateShape(geo);
	renderItem = new RenderItem(centreShape, &pose, color);
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