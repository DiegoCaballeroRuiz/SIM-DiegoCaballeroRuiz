#pragma once

#include "GameObject.h"

class StaticSolid : public GameObject
{
protected:
	physx::PxRigidStatic* body;

public:
	StaticSolid(Vector3 pos, physx::PxPhysics* gPhysics, physx::PxScene* mScene, physx::PxShape* shape, Vector4 color = { 1.0, 1.0, 1.0, 1.0 }, double lifeTime = 100.0);
	~StaticSolid();


	inline physx::PxRigidStatic* getBody() { return body; }

	inline void addForce(Vector3 force) override {}
	
	void integrate(double dt) override {}

	inline double getMass() const override { return 0; }
	inline void setMass(double newMass) {}
	inline physx::PxTransform* getTransform() override { return &body->getGlobalPose(); }
};

