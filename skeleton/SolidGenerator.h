#pragma once

#include "PxPhysics.h"
#include <random>
#include "core.hpp"
#include <vector>

class Solid;
class GameObject;
class SolidGenerator
{
protected:
	Vector3 position, offset;
	double probGen, mass;

	std::mt19937 mt;

	virtual Solid* genSolid() = 0;
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;
public:
	SolidGenerator(Vector3 positionOffset, double probGen, double mass, physx::PxScene* scene, physx::PxPhysics* gPhysics);
	virtual ~SolidGenerator() = 0;

	std::vector<GameObject*> generate(int nSolids);

	Vector3 getPos();
	void setPos(Vector3 newPos);

	Vector3 getOffset();
	void setOffset(Vector3 newOffset);
};

