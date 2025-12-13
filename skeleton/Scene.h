#pragma once

#include "InputListener.h"

namespace physx {
	class PxTransform;
	class PxScene;
	class PxPhysics;
}

class Scene : public InputListener
{
public:
	Scene(physx::PxScene* scene, physx::PxPhysics* physics);
	virtual void integrate(double t) = 0;

	virtual void start() = 0;
	virtual ~Scene() = 0;

protected:
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;
};

