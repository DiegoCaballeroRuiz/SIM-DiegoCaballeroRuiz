#include "Solid.h"

Solid::Solid(Vector3 pos, double mass, physx::PxPhysics* gPhysics, physx::PxScene* mScene, physx::PxGeometry geo, Vector4 color, double lifeTime)
	: GameObject(pos, mass, geo, color, lifetime)
{
	body = gPhysics->createRigidDynamic(pose);
	body->attachShape(*renderItem->shape);

	body->setLinearDamping(.9);
	physx::PxRigidBodyExt::setMassAndUpdateInertia(*body, mass);

	mScene->addActor(*body);
}

Solid::~Solid()
{
	GameObject::~GameObject();

	auto scene = body->getScene();
	scene->removeActor(*body);
}

void 
Solid::addForce(Vector3 force) {
	body->addForce(force);
}

