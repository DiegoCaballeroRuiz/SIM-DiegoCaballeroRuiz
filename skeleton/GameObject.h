#pragma once
#include <PxPhysics.h>
#include "RenderUtils.hpp"

class GameObject
{
protected:
	physx::PxTransform pose;
	RenderItem* renderItem;

	double lifetime, timeAlive;
	bool markedDead = false;
public:
	GameObject(Vector3 pos, double mass, physx::PxGeometry geo = physx::PxSphereGeometry(.5), Vector4 color = { 1.0, 1.0, 1.0, 1.0 }, double lifeTime = 100.0);
	~GameObject();

	virtual void integrate(double delta);

	inline physx::PxTransform* getTransform() { return &pose; }
	bool isAlive() const { return markedDead || timeAlive < lifetime; }

	inline void kill() { markedDead = true; }

	virtual void addForce(Vector3 force) = 0;

	virtual double getMass() const = 0;
	virtual void setMass(double newMass) = 0;
};

