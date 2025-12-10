#include "Scene.h"

Scene::Scene(physx::PxScene* scene, physx::PxPhysics* physics) 
	: gScene(scene), gPhysics(physics)
{
}

Scene::~Scene() {

}

