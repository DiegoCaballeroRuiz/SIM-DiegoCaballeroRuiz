#pragma once
#include <PxPhysics.h>
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

class GameObject
{
protected:
	RenderItem* renderItem;

	double lifetime, timeAlive;
	bool markedDead = false;
	physx::PxShape* shape;
public:
	GameObject(Vector4 color = { 1.0, 1.0, 1.0, 1.0 }, double lifeTime = 100.0);
	~GameObject();

	virtual void integrate(double delta);

	bool isAlive() const { return markedDead || timeAlive < lifetime; }

	inline void kill() { markedDead = true; }

	virtual void addForce(Vector3 force) = 0;

	virtual double getMass() const = 0;
	virtual void setMass(double newMass) = 0;
	virtual physx::PxTransform* getTransform() = 0;
	virtual Vector3 getVelocity() const = 0;
};

