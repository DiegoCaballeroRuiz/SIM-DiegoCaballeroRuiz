#include "UniformGenerator.h"
#include "Particle.hpp"

UniformGenerator::UniformGenerator(Vector3 position, Vector3 direction, double speed, double duration, double probGen, double mass
	, double posVariation, double directionVariation, double durationVariation, double speedVariation, Vector4 color)
	: ParticleGenerator(position, direction, speed, duration, probGen, mass), posVariation(posVariation), directionVariation(directionVariation),
	durationVariation(durationVariation), speedVariation(speedVariation), color(color)
{
	std::random_device randomDevice;
	mt = std::mt19937(randomDevice());
}

Particle* 
UniformGenerator::genParticle() {
	Vector3 pos = position + Vector3(u(mt), u(mt), u(mt)) * posVariation;

	Vector3 dir = direction + Vector3(u(mt), u(mt), u(mt)) * directionVariation;
	double sp = speed + u(mt) * directionVariation;
	Vector3 vel = dir * sp;

	double dur = duration + u(mt) * durationVariation;

	Particle* particle = new Particle(pos, vel, 0.9, mass, color, dur);
	return particle;
}