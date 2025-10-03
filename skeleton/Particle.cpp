#include "Particle.hpp"

#include <cmath>

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 accel, double damp) : velocity(vel), pose(pos), acceleration(accel), damping(damp)
{
	const physx::PxSphereGeometry geo = physx::PxSphereGeometry(1.0);
	physx::PxShape* centreShape = CreateShape(geo);
	renderItem = new RenderItem(centreShape, &pose, { 1, 0, 1, 1 });
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void
Particle::integrate(double t) {
	velocity += acceleration * t;
	pose.p += velocity * t;
	velocity *= std::pow(damping, t);	
}