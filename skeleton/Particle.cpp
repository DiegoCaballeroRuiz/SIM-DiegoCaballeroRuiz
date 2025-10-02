#include "Particle.hpp"

Particle::Particle(Vector3 pos, Vector3 vel) : velocity(vel), pose(pos)
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
	pose.p += velocity * t;
}