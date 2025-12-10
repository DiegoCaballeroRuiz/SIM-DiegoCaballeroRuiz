#pragma once

#include "SolidGenerator.h"
#include <PxPhysics.h>

class GaussianSolidGenerator : public SolidGenerator
{
protected:
	std::normal_distribution<double> d{ 0.0, 1.0 };
	double posVariation;
	Vector4 color;

	physx::PxGeometry geo;

	Solid* genSolid() override;
public:
	GaussianSolidGenerator(Vector3 position, double probGen, double mass, physx::PxScene* gScene, physx::PxPhysics* gPhysics, physx::PxGeometry geo = physx::PxSphereGeometry(.5), Vector4 color = {1.0, 1.0, 1.0, 1.0});
	~GaussianSolidGenerator() {}
};

