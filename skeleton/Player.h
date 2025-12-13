#pragma once

#include "Solid.h"
#include "ParticleSystem.h"
#include "InputListener.h"
#include <queue>

class Player : public Solid, public ParticleSystem, public InputListener
{
protected:
	double speed;

	SolidGenerator* ballGenerator;
	ForceGenerator* servingForceGen;
	ForceGenerator* hitForceGen;

	std::queue<ForceGenerator*> forcesToRemove;
	std::queue<SolidGenerator*> solidGenToRemove;

	bool hasServed;

	void serve();
	void hit();
	void processRemovals();
public:
	Player(Vector3 pos, physx::PxPhysics* gPhysics, physx::PxScene* mScene, double speed = 10.0, double serveForce = 25.0, double width = 0.5 , double height = 1.8, double mass = 85.0, Vector4 color = {0.6, 0.4, 0.37, 1.0});
	~Player();

	void processKey(unsigned char c) override;
	void update(double delta) override;
};

