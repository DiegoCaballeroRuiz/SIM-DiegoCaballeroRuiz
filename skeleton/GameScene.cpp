#include "GameScene.h"

#include "Cube.h"
#include "GaussianGenerator.h"
#include "ExplosionForceGenerator.h"
#include "GravityForceGenerator.h"
#include "PointProyectileGenerator.h"
#include "ParticleSystem.h"
#include "StaticSolid.h"
#include "Particle.hpp"
#include "GaussianSolidGenerator.h"
#include "Player.h"

GameScene::GameScene(physx::PxScene* scene, physx::PxPhysics* physics) 
	: Scene(scene, physics), nextConfettiActivation(true), nextWind(true)
{
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
	confetti->update(t);
	ball->update(t);
	wind->update(t);
	rain->update(t);
	rafaNadal->update(t);

	processRemovals();
}

void 
GameScene::start() {
	// Game Objects
	floor = new StaticSolid(Vector3(-15), gPhysics, gScene, CreateShape(physx::PxBoxGeometry(100.0, 20, 100.0)), { 0.8, 0.8, 0.25, 1.0 });
	wall = new StaticSolid(Vector3(.0, .0, -15), gPhysics, gScene, CreateShape(physx::PxBoxGeometry(100.0, 200.0, 1.0)), { 0.0, 0.5, 0.2, 1.0 });
	wallLine = new StaticSolid(Vector3(.0, 6, -15), gPhysics, gScene, CreateShape(physx::PxBoxGeometry(100.0, 0.3, 1.5)), { .0, .0, .0, 1.0 });

	//Set gravitational force
	gravity = new GravityForceGenerator(10.0);

	//Confetti
	confetti = new ParticleSystem(Vector3(0, 100.0, 0));
	
	GaussianGenerator* confetti1 = new GaussianGenerator(Vector3(.0), Vector3(.0), 5.0, 10.0, 0.2, 1.5, 1.0, .0, .0, 1.0, { 1.0, 0.0, 0.0, 1.0 });
	GaussianGenerator* confetti2 = new GaussianGenerator(Vector3(.0), Vector3(.0), 5.0, 10.0, 0.2, 1.5, 1.0, .0, .0, 1.0, { .0, 1.0, 0.0, 1.0 });
	GaussianGenerator* confetti3 = new GaussianGenerator(Vector3(.0), Vector3(.0), 5.0, 10.0, 0.2, 1.5, 1.0, .0, .0, 1.0, { .0, .0, 1.0, 1.0 });
	GaussianGenerator* confetti4 = new GaussianGenerator(Vector3(.0), Vector3(.0), 5.0, 10.0, 0.2, 1.5, 1.0, .0, .0, 1.0, { 1.0, 1.0, 1.0, 1.0 });
	GaussianGenerator* confetti5 = new GaussianGenerator(Vector3(.0), Vector3(.0), 5.0, 10.0, 0.2, 1.5, 1.0, .0, .0, 1.0, { 1.0, 1.0, .0, 1.0 });

	confettiGens = { confetti1, confetti2, confetti3, confetti4, confetti5 };
	confettiForce = new ExplosionForceGenerator(Vector3(100.0, 0.0, 0.0), confetti->getPosition(), 5.0);
	forces.push_back(gravity);
	confetti->registerForceGenerator(gravity);

	confettiCenter = new Particle(confetti->getPosition(), Vector3(0.0), 0.9, 1, Vector4(1.0, 0.0, 1.0, 1.0));

	// Tennis ball
	ball = new ParticleSystem(Vector3(0.0), 1);
	ballGen = new GaussianSolidGenerator(Vector3(.0), 10.0, .02, .0, 5.0, gScene, gPhysics, CreateShape(physx::PxSphereGeometry(1.)), Vector4{ 1.0, 1.0, .2, 1.0 });
	proyectileBallGen = new PointProyectileGenerator(Vector3(.0), Vector3(1.0, .0, .0), 40, 25, 5.0, .05, { .0, .0, .0, 1.0 });

	shootForce = new ForceGenerator();
	forces.push_back(shootForce);
	ball->registerForceGenerator(gravity);

	//Windy weather
	wind = new ParticleSystem(Vector3(.0));
	windForce = new ConstantAccelForceGenerator(100, Vector3(-1.0, .0, .0));
	windGen = new GaussianGenerator(Vector3(.0), Vector3(.0), 5.0, 3.0, .2, .1, 500.0, .0, 1.5, .5, Vector4(1.0, 1.0, 1.0, 1.0));
	wind->registerForceGenerator(windForce);

	//Rainy weather
	rain = new ParticleSystem(Vector3(.0, 100, .0));
	rainGen = new GaussianGenerator(Vector3(.0), Vector3(.0), .0, 30.0, 1.0, .01, 200.0, .0, .0, .0, Vector4(.0, 0.25, 1.0, 1.0));
	rain->registerForceGenerator(gravity);

	//Player
	rafaNadal = new Player(Vector3(0, 0, 0), gPhysics, gScene);
	GetCamera()->setPosition(Vector3(5, 10, 10));
	GetCamera()->setDirection(Vector3(-2.5, .0, -5.0));
	inputListeners.push_back(rafaNadal);
}

void 
GameScene::processKey(unsigned char c) {
	switch (c) {
	case 'c':
		toggleConfetti(nextConfettiActivation);
		nextConfettiActivation = !nextConfettiActivation;
		break;
	case 'v':
		toggleWind(nextWind);
		nextWind = !nextWind;
		break;
	case 'l':
		toggleRain(nextRain);
		nextRain= !nextRain;
		break;
	default: 
		for (InputListener* listener : inputListeners)
			listener->processKey(c);
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
		wind->registerParticleGenerator(windGen, 20);
		rain->registerForceGenerator(windForce);
		ball->registerForceGenerator(windForce);
		confetti->registerForceGenerator(windForce);
	}

	else {
		wind->deRegisterParticleGenerator(windGen);
		rain->deRegisterForceGenerator(windForce);
		confetti->deRegisterForceGenerator(windForce);
		ball->deRegisterForceGenerator(windForce);
	}
}

void 
GameScene::toggleRain(bool activate) {
	if (activate) {
		rain->registerParticleGenerator(rainGen, 10);
	}

	else {
		rain->deRegisterParticleGenerator(rainGen);
	}
}

void 
GameScene::processRemovals() {
	while (!forceToRemove.empty()) {
		auto pair = forceToRemove.front();
		forceToRemove.pop();

		pair.first->deRegisterForceGenerator(pair.second);
	}

	while (!pGenToRemove.empty()) {
		auto pair = pGenToRemove.front();
		pGenToRemove.pop();

		pair.first->deRegisterParticleGenerator(pair.second);
	}

	while (!sGenToRemove.empty()) {
		auto pair = sGenToRemove.front();
		sGenToRemove.pop();

		pair.first->deRegisterSolidGenerator(pair.second);
	}
}
