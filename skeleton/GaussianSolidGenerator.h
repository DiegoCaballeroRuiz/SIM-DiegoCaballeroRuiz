#pragma once

#include "SolidGenerator.h"
#include <PxPhysics.h>

class GaussianSolidGenerator : public SolidGenerator
{
protected:
	std::normal_distribution<double> d{ 0.0, 1.0 };
	double posVariation, duration;
	Vector4 color;

	physx::PxShape* shape;

	Solid* genSolid() override;
public:
	GaussianSolidGenerator(Vector3 position, double probGen, double mass, double posVariation, double duration, physx::PxScene* gScene, physx::PxPhysics* gPhysics, physx::PxShape* shape, Vector4 color = {1.0, 1.0, 1.0, 1.0});
	~GaussianSolidGenerator() {}
};

