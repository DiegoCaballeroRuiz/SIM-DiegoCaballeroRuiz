#include "SolidGenerator.h"

#include "Solid.h"

SolidGenerator::SolidGenerator(Vector3 position, double probGen, double mass, physx::PxScene* gScene, physx::PxPhysics* gPhysics)
	: position(Vector3(0.0)), offset(position), probGen(probGen), mass(mass), gPhysics(gPhysics), gScene(gScene)
{
}

SolidGenerator::~SolidGenerator() {}

std::vector<GameObject*>
SolidGenerator::generate(int nSolids) {
	std::vector<GameObject*> solids;

	for (int i = 0; i < nSolids; ++i) {
		auto solid = genSolid();
		if (solid != nullptr) solids.push_back(solid);
	}

	return solids;
}

Vector3
SolidGenerator::getPos() {
	return position;
}

void
SolidGenerator::setPos(Vector3 newPos) {
	position = newPos;
}

Vector3
SolidGenerator::getOffset() {
	return offset;
}

void
SolidGenerator::setOffset(Vector3 newOffset) {
	offset = newOffset;
}