#include "StaticSolid.h"

StaticSolid::StaticSolid(Vector3 pos, physx::PxPhysics* gPhysics, physx::PxScene* mScene, physx::PxShape* shape, Vector4 color, double lifeTime, bool visible) 
	: GameObject(color, lifeTime), visible(visible)
{
	body = gPhysics->createRigidStatic(physx::PxTransform(pos));

	body->attachShape(*shape);
	mScene->addActor(*body);
	if(visible)
		renderItem = new RenderItem(shape, body, color);
}

StaticSolid::~StaticSolid() {
	if (!visible) return;
	DeregisterRenderItem(renderItem);
	delete renderItem;
}
