#include "PointProyectileGenerator.h"

#include "Proyectile.h"

PointProyectileGenerator::PointProyectileGenerator(Vector3 positionOffset, Vector3 direction, double realSpeed, double targetSpeed, double duration, double realMass, Vector4 color) 
	: ParticleGenerator(positionOffset, direction, targetSpeed, duration, 1.0, realMass), realSpeed(realSpeed), color(color)
{
}

PointProyectileGenerator::~PointProyectileGenerator() {}

Particle* 
PointProyectileGenerator::genParticle() {
	Vector3 realVel = realSpeed * direction;
	Vector3 targetVel = speed * direction;

	Proyectile* p = new Proyectile(position, realVel, targetVel, 0.9, mass, color);
	return p;
}