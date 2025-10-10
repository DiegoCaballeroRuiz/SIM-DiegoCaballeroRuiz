#include "Proyectile.h"

Proyectile::Proyectile(Vector3 pos, Vector3 realVel, Vector3 targetVelocity, Vector3 accel, double damp, double mass, Vector4 color) 
	: Particle(pos, targetVelocity, accel, damp, color), realVelocity(realVel), realMass(mass)
{
	setSimulatedMass();
}

void 
Proyectile::setSimulatedMass() {
	targetMass = realMass * (realVelocity.magnitudeSquared() / velocity.magnitudeSquared());
}

