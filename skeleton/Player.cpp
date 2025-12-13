#include "Player.h"

#include <climits>
#include <iostream>
#include "GaussianSolidGenerator.h"
#include "ForceGenerator.h"
#include "StrikeForceGenerator.h"

Player::Player(Vector3 pos, physx::PxPhysics* gPhysics, physx::PxScene* mScene, double speed, double serveForce, double width, double height, double mass, Vector4 color)
	: ParticleSystem(pos, 1), Solid(pos, mass, gPhysics, mScene, CreateShape(physx::PxBoxGeometry(width, height, width)), color, INFINITY), speed(speed), hasServed(false)
{
	body->setLinearDamping(0.9);
	body->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlags(
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X |
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z
	));

	ballGenerator = new GaussianSolidGenerator(Vector3(width * 2, .0, .0), 10.0, 0.02, .0, INFINITY, mScene, gPhysics, CreateShape(physx::PxSphereGeometry(0.06)), Vector4{ 1.0, 1.0, 0.0, 1.0 });
	servingForceGen = new ForceGenerator(Vector3{.0, (float)serveForce, .0});
	hitForceGen = new StrikeForceGenerator(100.0, Vector3(.0, .25, -1.0), 2 * height);
}

Player::~Player() {
	ParticleSystem::~ParticleSystem();
	Solid::~Solid();
}

void 
Player::processKey(unsigned char c) {

	switch (c) {
	case 'w':
		body->addForce(Vector3(.0, .0, speed));
		break;

	case 'a':
		body->addForce(Vector3(.0, .0, -speed));
		break;

	case 's':
		body->addForce(Vector3(speed, .0, .0));
		break;

	case 'd':
		body->addForce(Vector3(-speed, .0, .0));
		break;

	case 'j':
		if (hasServed) hit();
		else serve();
	break;
	default: break;
	}
}

void 
Player::update(double delta) {
	hitForceGen->setPosition(pos);
	ParticleSystem::update(delta);
	
	pos = body->getGlobalPose().p;
	processRemovals();
}

void 
Player::serve() {
	registerSolidGenerator(ballGenerator, 1);
	registerForceGenerator(servingForceGen);

	forcesToRemove.push(servingForceGen);
	solidGenToRemove.push(ballGenerator);

	hasServed = true;
}

void 
Player::hit() {
	registerForceGenerator(hitForceGen);
	forcesToRemove.push(hitForceGen);
}


void 
Player::processRemovals() {
	while (!solidGenToRemove.empty()) {
		deRegisterSolidGenerator(solidGenToRemove.front());
		solidGenToRemove.pop();
	}

	while (!forcesToRemove.empty()) {
		deRegisterForceGenerator(forcesToRemove.front());
		forcesToRemove.pop();
	}
}
