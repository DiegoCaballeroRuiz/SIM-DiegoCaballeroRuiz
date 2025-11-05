#include "GravityForceGenerator.h"

#include "Particle.hpp"

GravityForceGenerator::GravityForceGenerator(double gravityAccel) 
	: ConstantAccelForceGenerator(gravityAccel, Vector3(.0, -1.0, .0))
{
}

GravityForceGenerator::~GravityForceGenerator() 
{
}
