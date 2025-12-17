#pragma once

#include "Solid.h"
#include "ParticleSystem.h"
#include "InputListener.h"
#include "UserData.h"

#include <queue>

class Player : public Solid, public ParticleSystem
{
protected:
	//Parameters
	double speed;
	bool raining;
	bool hasServed;
	double remainigHitCooldown;
	const int HIT_COOLDOWN = 1;

	//Ball related
	SolidGenerator* ballGenerator;
	ForceGenerator* servingForceGen;
	ForceGenerator* hitForceGen;
	Solid* ball;
	UserData ballData;

	//1 frame removers
	std::queue<ForceGenerator*> forcesToRemove;
	std::queue<SolidGenerator*> solidGenToRemove;

	//Friction
	ForceGenerator* friction;

	//Methods
	void serve();
	void hit();
	void processRemovals();
	void tryRegisterBall();
public:
	Player(Vector3 pos, physx::PxPhysics* gPhysics, physx::PxScene* mScene, double speed = 300.0, double serveForce = 25.0, double width = 0.25 , double height = .9, double mass = 10.0, Vector4 color = {.6, .2, .0, 1.0});
	~Player();

	void processInput();
	void update(double delta) override;
	inline void setRaining(bool isRaining) { raining = isRaining; }
};

