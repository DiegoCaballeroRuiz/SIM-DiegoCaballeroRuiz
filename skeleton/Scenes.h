#pragma once
#include <vector>
#include "Scene.h"
#include "core.hpp"

class ParticleSystem;
class Scene2 : public Scene {
private:
	ParticleSystem* pSys;

public:
	Scene2(physx::PxScene* scene, physx::PxPhysics* physics);
	~Scene2();
	void integrate(double t) override;
	void start() override;
	void processKey(unsigned char c) override;
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) override {}
};