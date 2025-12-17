#pragma once


#include "GameObject.h"
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"

class Solid : public GameObject
{
protected:
	physx::PxRigidDynamic* body;
	
public:
	Solid(Vector3 pos, double mass, physx::PxPhysics* gPhysics, physx::PxScene* mScene, physx::PxShape* shape, Vector4 color = { 1.0, 1.0, 1.0, 1.0 }, double lifeTime = 100.0);
	~Solid();

	inline physx::PxRigidDynamic* getBody() { return body; }

	void addForce(Vector3 force) override;
	void integrate(double dt) override;

	inline double getMass() const override { return body->getMass(); }
	inline Vector3 getVelocity() const override { return body->getLinearVelocity(); }
	inline void setMass(double newMass) { physx::PxRigidBodyExt::setMassAndUpdateInertia(*body, newMass); }
	inline physx::PxTransform* getTransform() override { return &body->getGlobalPose(); }
};

