#pragma once

#include "ParticleGen.h"

class GaussianGenerator : public ParticleGenerator
{
protected:
	std::normal_distribution<double> d{ 0.0, 1.0 };
	double posVariation, directionVariation, durationVariation, speedVariation;

	Particle* genParticle() override;
public:
	GaussianGenerator(Vector3 position, Vector3 direction, double speed, double duration, double probGen
	, double posVariation, double directionVariation, double durationVariation, double speedVariation);
	~GaussianGenerator() {}
};

