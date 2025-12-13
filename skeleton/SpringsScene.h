#pragma once

#include "Scene.h"

class ParticleSystem;
class ForceGenerator;
class SpringForceGenerator;
class Particle;
class SpringsScene : public Scene
{
	ParticleSystem* pSys;
	SpringForceGenerator* springGen;
	ForceGenerator* gravity;
	Particle* anchor;

	bool nextSpringActivation = false;

	void toggleSpring(bool activate);
public:
	SpringsScene(physx::PxScene* scene, physx::PxPhysics* physics);
	~SpringsScene();

	void integrate(double t) override;

	void start() override;
	void processKey(unsigned char c) override;
};

