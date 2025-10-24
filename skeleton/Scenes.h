#pragma once
#include <vector>
#include "Scene.h"
#include "core.hpp"
#include "ParticleSystem.h"

class Scene2 : public Scene {
private:
	ParticleSystem pSys;

public:
	Scene2() : Scene() {}
	~Scene2();
	void integrate(double t) override;
	void start() override;
	void processKey(unsigned char c, const physx::PxTransform* camera) override;
};