#include "GaussianSolidGenerator.h"

#include "Solid.h"

GaussianSolidGenerator::GaussianSolidGenerator(Vector3 position, double probGen, double mass, physx::PxScene* gScene, physx::PxPhysics* gPhysics, 
	physx::PxGeometry geo, Vector4 color)

	: SolidGenerator(position, probGen, mass, gScene, gPhysics), posVariation(posVariation), color(color), geo(geo)
{
	std::random_device randomDevice;
	mt = std::mt19937(randomDevice());
}

Solid*
GaussianSolidGenerator::genSolid() {
	if (std::abs(d(mt)) > probGen) return nullptr;

	Vector3 pos = position + Vector3(d(mt), d(mt), d(mt)) * posVariation;

	Solid* solid = new Solid(pos, mass, gPhysics, gScene, geo, color);
	return solid;
}