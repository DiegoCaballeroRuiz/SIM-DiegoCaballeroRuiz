#pragma once

#include "ParticleGenerator.h"
class PointProyectileGenerator : public ParticleGenerator
{
	double realSpeed;
	Vector4 color;

	Particle* genParticle() override;
public:

	PointProyectileGenerator(Vector3 positionOffset, Vector3 direction, double realSpeed, double targetSpeed, double duration, double realMass, Vector4 color);
	~PointProyectileGenerator();
};

