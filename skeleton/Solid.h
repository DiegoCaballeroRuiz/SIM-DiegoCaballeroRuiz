#pragma once


#include "GameObject.h"

class Solid : public GameObject
{
protected:
	physx::PxRigidDynamic* body;
	
public:
	Solid(Vector3 pos, double mass, physx::PxPhysics* gPhysics, physx::PxScene* mScene, physx::PxGeometry geo = physx::PxSphereGeometry(.5), Vector4 color = { 1.0, 1.0, 1.0, 1.0 }, double lifeTime = 100.0);
	~Solid();


	inline physx::PxRigidDynamic* getBody() { return body; }

	void addForce(Vector3 force) override;

	inline double getMass() const override { return body->getMass(); }
	inline void setMass(double newMass) { physx::PxRigidBodyExt::setMassAndUpdateInertia(*body, newMass); }
};

