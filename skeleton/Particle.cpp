#include "Particle.hpp"

#include <cmath>

Particle::Particle(Vector3 pos, Vector3 vel, double damp, double mass, Vector4 color, double lifetime) 
	: GameObject(color, lifetime), pose(pos), velocity(vel), damping(damp), mass(mass), invMass(std::pow(mass, -1)), forceSum(0.0, 0.0, 0.0)
{
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(.2)), &pose, color);
}

Particle::~Particle() {
	GameObject::~GameObject();
}

void
Particle::integrate(double t) {
	GameObject::integrate(t);
	velocity += forceSum * invMass * t;
	pose.p += velocity * t;
	velocity *= std::pow(damping, t);	
	
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

void
Particle::setMass(double newMass) {
	mass = newMass;
	invMass = std::pow(mass, -1);
}