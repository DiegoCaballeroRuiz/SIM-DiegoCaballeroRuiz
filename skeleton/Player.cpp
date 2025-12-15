#include "Player.h"

#include <climits>
#include "GaussianSolidGenerator.h"
#include "ForceGenerator.h"
#include "KeyboardState.h"
#include "StrikeForceGenerator.h"

Player::Player(Vector3 pos, physx::PxPhysics* gPhysics, physx::PxScene* mScene, double speed, double serveForce, double width, double height, double mass, Vector4 color)
	: ParticleSystem(pos, 1), Solid(pos, mass, gPhysics, mScene, CreateShape(physx::PxBoxGeometry(width, height, width)), color, INFINITY), speed(speed), hasServed(false), remainigHitCooldown(0), ball(nullptr)
{
	body->setLinearDamping(0.1);
	body->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlags(
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X |
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z
	));

	ballGenerator = new GaussianSolidGenerator(Vector3(width * 2, .0, .0), 10.0, 0.02, .0, INFINITY, mScene, gPhysics, CreateShape(physx::PxSphereGeometry(0.1)), Vector4{ 1.0, 1.0, 0.0, 1.0 });
	servingForceGen = new ForceGenerator(Vector3{.0, (float)serveForce, .0});
	hitForceGen = new StrikeForceGenerator(-75.0, Vector3(.0, .0, 1.0), 2.5 * height);

	ballData.identity = whoami::BALL;
}

Player::~Player() {
	ParticleSystem::~ParticleSystem();
	Solid::~Solid();
}

void 
Player::processInput() {

	Vector3 forceToAdd = Vector3(.0);
	auto input = KeyboardState::Instance();
	bool somethingPressed = false;

	//Movement input
	if (input->isKeyDown('w')) {
		forceToAdd = Vector3(.0, .0, -1.0);
		somethingPressed = true;
	}
	 
	else if (input->isKeyDown('s')) {
		forceToAdd = Vector3(.0, .0, 1.0);
		somethingPressed = true;
	}

	if (input->isKeyDown('a')) {
		forceToAdd = Vector3(-1.0, .0, .0);
		somethingPressed = true;
	}

	else if (input->isKeyDown('d')) {
		forceToAdd = Vector3(1.0, .0, .0);
		somethingPressed = true;
	}

	forceToAdd = forceToAdd.getNormalized() * speed;
	if (somethingPressed) body->addForce(forceToAdd);

	// Hitting input
	if (input->isKeyDown('j') && remainigHitCooldown < 0) {
		if (hasServed) hit();
		else serve();

		remainigHitCooldown = HIT_COOLDOWN;
	}
}

void 
Player::update(double delta) {
	processInput();
	remainigHitCooldown -= delta;

	pos = body->getGlobalPose().p;
	hitForceGen->setPosition(pos);
	GetCamera()->setPosition(pos + Vector3(0, 5, 8));
	
	ParticleSystem::update(delta);
	tryRegisterBall();
	
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

void 
Player::tryRegisterBall() {
	if (ball != nullptr || gObjects.size() == 0) return;

	ball = static_cast<Solid*>(gObjects[0]);
	ball->getBody()->userData = &ballData;
}
