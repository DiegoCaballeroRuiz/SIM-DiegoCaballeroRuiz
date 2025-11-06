#include "Proyectile.h"

#include <cmath>

Proyectile::Proyectile(Vector3 pos, Vector3 realVel, Vector3 targetVelocity, double damp, double mass, Vector4 color, double lifeTime) 
	: Particle(pos, targetVelocity, damp, mass, color, lifeTime), realVelocity(realVel)
{
	setSimulatedMass();
}

void 
Proyectile::setSimulatedMass() {
	targetMass = mass * (realVelocity.magnitudeSquared() / velocity.magnitudeSquared());
	invTargetMass = std::pow(targetMass, -1);
}

void 
Proyectile::setMass(double newMass) {
	Particle::setMass(newMass);
	setSimulatedMass();
}

void 
Proyectile::integrate(double t) {
	velocity += forceSum * invTargetMass * t;
	pose.p += velocity * t;
	velocity *= std::pow(damping, t);
	timeAlive += t;
	forceSum = Vector3(0.0);
}
