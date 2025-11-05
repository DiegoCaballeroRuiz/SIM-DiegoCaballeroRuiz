#pragma once
#include "ConstantAccelForceGenerator.h"

class GravityForceGenerator : public ConstantAccelForceGenerator
{
public:
	GravityForceGenerator(double gravityAccel);
	~GravityForceGenerator();
};

