#include "StaticSolid.h"

StaticSolid::StaticSolid(Vector3 pos, physx::PxPhysics* gPhysics, physx::PxScene* mScene, physx::PxShape* shape, Vector4 color, double lifeTime) 
	: GameObject(color, lifeTime)
{
	body = gPhysics->createRigidStatic(physx::PxTransform(pos));
	renderItem = new RenderItem(shape, body, color);
	body->attachShape(*shape);

	mScene->addActor(*body);
}

StaticSolid::~StaticSolid() {
	DeregisterRenderItem(renderItem);
	delete renderItem;
}
