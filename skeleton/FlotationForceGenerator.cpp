#include "FlotationForceGenerator.h"

#include "Particle.hpp"

FlotationForceGenerator::FlotationForceGenerator(double liquidHeight, double volume, Vector3 pos, double liquidDensity, double gravity, double pHeight)
	: ForceGenerator(Vector3(.0), pos), height(liquidHeight), volume(volume), density(liquidDensity), gravity(gravity), particleHeightHalf(pHeight * 0.5)
{ 
}

FlotationForceGenerator::~FlotationForceGenerator() {}

void 
FlotationForceGenerator::applyForce(Particle* particle) {
	double inmersed;

	double particleYPos = particle->getTransform()->p.y;

	if (particleYPos - height > particleHeightHalf) inmersed = .0;
	else if (height - particleYPos > particleHeightHalf) inmersed = 1.0;
	else inmersed = (height - position.y) / (particleHeightHalf * 2);

	particle->addForce(Vector3(.0, density * volume * inmersed * gravity, .0));
}
