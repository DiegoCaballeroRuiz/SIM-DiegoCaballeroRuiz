#include "Solid.h"

#include "PxRigidDynamic.h"

Solid::Solid(Vector3 pos, double mass, physx::PxPhysics* gPhysics, physx::PxScene* mScene, physx::PxShape* shape, Vector4 color, double lifeTime)
	: GameObject(color, lifeTime)
{
	body = gPhysics->createRigidDynamic(physx::PxTransform(pos));
	body->attachShape(*shape);
	renderItem = new RenderItem(shape, body, color);
	body->setMass(mass);

	body->setLinearDamping(.999);
	physx::PxRigidBodyExt::setMassAndUpdateInertia(*body, mass);

	mScene->addActor(*body);
}

Solid::~Solid()
{
	GameObject::~GameObject();

	auto scene = body->getScene();
	scene->removeActor(*body);
	body = nullptr;
}

void 
Solid::addForce(Vector3 force) {
	body->addForce(force);
}
void 
Solid::integrate(double dt) {
	GameObject::integrate(dt);
}

