#pragma once
#include "ParticleGenerator.h"

class UniformGenerator : public ParticleGenerator
{
protected:
	std::uniform_real_distribution<double> u{ 0.0, 1.0 };
	double posVariation, directionVariation, durationVariation, speedVariation;

	Vector4 color;

	Particle* genParticle() override;
public:
	UniformGenerator(Vector3 position, Vector3 direction, double speed, double duration, double probGen, double mass
		, double posVariation, double directionVariation, double durationVariation, double speedVariation, Vector4 color = { 1.0, 1.0, 1.0, 1.0 });

	~UniformGenerator() {}
};