#include "GameScene.h"

#include "GaussianGenerator.h"
#include "ExplosionForceGenerator.h"
#include "GravityForceGenerator.h"
#include "PointProyectileGenerator.h"
#include "ParticleSystem.h"
#include "StaticSolid.h"
#include "Particle.hpp"
#include "GaussianSolidGenerator.h"
#include "WindForceGenerator.h"
#include "Player.h"

#include <iostream>

GameScene::GameScene(physx::PxScene* scene, physx::PxPhysics* physics)
	: Scene(scene, physics), nextConfettiActivation(true), timeUntilNextWheatherEvent(.0), inWheatherEvent(false), currentFloorBounces(0), currentCheckCooldown(0)
{
	std::random_device device;
	rng = std::mt19937(device());
	wheatherEventDelayGenerator = std::uniform_real_distribution<double>(MIN_NEXT_WHEATHER_DELAY, MAX_NEXT_WHEATHER_DELAY);
	chance = std::uniform_real_distribution<double>(.0, 1.);

	timeUntilNextWheatherEvent = wheatherEventDelayGenerator(rng);

	wallData.identity = whoami::WALL;
	floorData.identity = whoami::FLOOR;
}

GameScene::~GameScene() {
	/*toggleWind(false);
	toggleRain(false);
	toggleConfetti(false);

	delete floor;
	delete wall;
	delete wallLine;

	delete confetti;
	for (auto force : forces)
		delete force;
	delete confettiCenter;

	delete ball;

	delete wind;

	delete rain;*/
}

void 
GameScene::integrate(double t) {
	manageWheather(t);
	currentCheckCooldown -= t;

	rafaNadal->update(t);

	confetti->update(t);
	globalWind->update(t);
	rain->update(t);
}

void 
GameScene::start() {
	// Game Objects
	hitWall = new StaticSolid(Vector3(.0, 6.5, -15.), gPhysics, gScene, CreateShape(physx::PxBoxGeometry(10.0, 13, 1.0)), { 0.0, 0.5, 0.2, 1.0 });
	backWall = new StaticSolid(Vector3(.0, 6.5, 30.), gPhysics, gScene, CreateShape(physx::PxBoxGeometry(10.0, 13, 1.0)), Vector4(.0), 100.0, false);
	leftWall = new StaticSolid(Vector3(-10, 6.5, .0), gPhysics, gScene, CreateShape(physx::PxBoxGeometry(1.0, 13, 30)), { 0.0, 0.5, 0.2, 1.0 });
	rightWall = new StaticSolid(Vector3(10, 6.5, .0), gPhysics, gScene, CreateShape(physx::PxBoxGeometry(1.0, 13, 30)), Vector4(.0), 100.0, false);
	wallLine = new StaticSolid(Vector3(.0, 6.5, -14.95), gPhysics, gScene, CreateShape(physx::PxBoxGeometry(10.0, 0.3, 1.)), { .0, .0, .0, 1.0 });
	hitWall->getBody()->userData = &wallData;
	backWall->getBody()->userData = &wallData;
	leftWall->getBody()->userData = &wallData;
	rightWall->getBody()->userData = &wallData;
	wallLine->getBody()->userData = &wallData;

	floor = new StaticSolid(Vector3(.0, -15, 0), gPhysics, gScene, CreateShape(physx::PxBoxGeometry(10.0, 20, 30.0), gPhysics->createMaterial(.0, 1., 0.1)), { 0.51, 0.75, 0.875, 1.0 });
	floor->getBody()->userData = &floorData;

	//Player
	rafaNadal = new Player(Vector3(0, 2, 0), gPhysics, gScene);

	//Camera
	GetCamera()->setDirection(Vector3(.0, -1, -5.0));

	//Set gravitational force
	gravity = new GravityForceGenerator(4);

	//Confetti
	confetti = new ParticleSystem(Vector3(0, 25, 0));
	
	GaussianGenerator* confetti1 = new GaussianGenerator(Vector3(.0), Vector3(.0), 2.0, 4.0, 0.2, 2.0, 1., .0, .0, 1.0, { 1.0, 0.0, 0.0, 1.0 });
	GaussianGenerator* confetti2 = new GaussianGenerator(Vector3(.0), Vector3(.0), 2.0, 4.0, 0.2, 2.0, 1., .0, .0, 1.0, { .0, 1.0, 0.0, 1.0 });
	GaussianGenerator* confetti3 = new GaussianGenerator(Vector3(.0), Vector3(.0), 2.0, 4.0, 0.2, 2.0, 1., .0, .0, 1.0, { .0, .0, 1.0, 1.0 });
	GaussianGenerator* confetti4 = new GaussianGenerator(Vector3(.0), Vector3(.0), 2.0, 4.0, 0.2, 2.0, 1., .0, .0, 1.0, { 1.0, 1.0, 1.0, 1.0 });
	GaussianGenerator* confetti5 = new GaussianGenerator(Vector3(.0), Vector3(.0), 2.0, 4.0, 0.2, 2.0, 1., .0, .0, 1.0, { 1.0, 1.0, .0, 1.0 });

	confettiGens = { confetti1, confetti2, confetti3, confetti4, confetti5 };
	confettiForce = new ExplosionForceGenerator(Vector3(100.0, 0.0, 0.0), confetti->getPosition(), 5.0);
	forces.push_back(gravity);
	confetti->registerForceGenerator(gravity);

	confettiCenter = new Particle(confetti->getPosition(), Vector3(0.0), 0.9, 1, Vector4(1.0, 0.0, 1.0, 1.0));

	//Windy weather
	globalWind = new ParticleSystem(Vector3(.0, 10, .0));
	windForce = new WindForceGenerator(Vector3(.0, 1., .0), 1, .1);
	windGen = new GaussianGenerator(Vector3(.0), Vector3(.0), 5.0, 3.0, .2, .1, 100.0, .0, 1.5, .5, Vector4(1.0, 1.0, 1.0, 1.0));
	globalWind->registerForceGenerator(windForce);

	//Rainy weather
	rain = new ParticleSystem(Vector3(.0, 100, .0));
	rainGen = new GaussianGenerator(Vector3(.0), Vector3(.0), .0, 30.0, 1.0, .01, 30.0, .0, .0, .0, Vector4(.0, 0.25, 1.0, 1.0));
	rain->registerForceGenerator(gravity);
}

void 
GameScene::processKey(unsigned char c) {
	switch (c) {
	case 'c':
		toggleConfetti(nextConfettiActivation);
		nextConfettiActivation = !nextConfettiActivation;
		break;
	default: 
		break;
	}
}

void 
GameScene::toggleConfetti(bool activate) {
	if (activate) {
		for (auto gen : confettiGens)
			confetti->registerParticleGenerator(gen, 1);

		confetti->registerForceGenerator(confettiForce);
	}
	else {
		for (auto gen : confettiGens)
			confetti->deRegisterParticleGenerator(gen);

		confetti->deRegisterForceGenerator(confettiForce);
	}
}

void 
GameScene::toggleWind(bool activate) {
	if (activate) {
		globalWind->registerParticleGenerator(windGen, 20);
		rain->registerForceGenerator(windForce);
		confetti->registerForceGenerator(windForce);
		rafaNadal->registerForceGenerator(windForce);
	}

	else {
		globalWind->deRegisterParticleGenerator(windGen);
		rain->deRegisterForceGenerator(windForce);
		rafaNadal->deRegisterForceGenerator(windForce);
		confetti->deRegisterForceGenerator(windForce);
	}
}

void 
GameScene::toggleRain(bool activate) {
	if (activate) {
		rain->registerParticleGenerator(rainGen, 10);
		rafaNadal->setRaining(true);
	} else {
		rain->deRegisterParticleGenerator(rainGen);
		rafaNadal->setRaining(false);
	}
}

void 
GameScene::manageWheather(double dt) {
	timeUntilNextWheatherEvent -= dt;
	if (timeUntilNextWheatherEvent > 0) return;

	timeUntilNextWheatherEvent = wheatherEventDelayGenerator(rng);

	if (inWheatherEvent) {
		toggleRain(false);
		toggleWind(false);
	}
	else {
		if (chance(rng) < RAIN_CHANCE) toggleRain(true);
		else toggleWind(true);
	}

	inWheatherEvent = !inWheatherEvent;
}

void 
GameScene::onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {
	if (currentCheckCooldown > 0) return;

	const UserData* data1 = reinterpret_cast<UserData*>(actor1->userData);
	const UserData* data2 = reinterpret_cast<UserData*>(actor2->userData);

	if (!data1 || !data2) return;

	if (data1->identity == whoami::BALL || data2->identity == whoami::BALL) {
		auto nonBallActorData = data1->identity == whoami::BALL ? data2 : data1;
		
		if (nonBallActorData->identity == whoami::FLOOR) {
			std::cout << "Floor was hit!\n";
			currentFloorBounces++;
			currentCheckCooldown = COLISION_CHECK_COOLDOWN;
			if (currentFloorBounces >= LOSING_FLOOR_BOUNCES) std::cout << "You lose!\n";
		}
		else if (nonBallActorData->identity == whoami::WALL) {
			std::cout << "Wall was hit!\n";
			currentFloorBounces = 0;
			currentCheckCooldown = COLISION_CHECK_COOLDOWN;
		}
	}
}