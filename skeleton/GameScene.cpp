#include "GameScene.h"

#include "Cube.h"
#include "GaussianGenerator.h"
#include "ExplosionForceGenerator.h"
#include "GravityForceGenerator.h"
#include "ParticleSystem.h"
#include "Particle.hpp"

GameScene::GameScene() : Scene(), nextConfettiActivation(true)
{
}

GameScene::~GameScene() {
	delete floor;
	delete wall;
	delete wallLine;

	delete confetti;
	for (auto force : forces)
		delete force;

	delete ball;
}

void 
GameScene::integrate(double t) {
	confetti->update(t);
	ball->update(t);

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
}

void 
GameScene::start() {
	// Game Objects
	floor = new Cube(Vector3(0), { 0.8, 0.8, 0.25, 1.0 }, 1000.0, .2, 1000.0);
	wall = new Cube(Vector3(0.0, 100.0, -100), { 0.0, 0.8, 0.2, 1.0 }, 1000.0, 200.0, 1.0);
	wallLine = new Cube(Vector3(0.0, 10, -100), { .0, .0, .0, 1.0 }, 1000.0, 5, 1.5);

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

	Particle* center = new Particle(confetti->getPosition(), Vector3(0.0), 0.9, 1, Vector4(1.0, 0.0, 1.0, 1.0));

	// Tennis ball
	ball = new ParticleSystem(Vector3(0.0), 1);
	ballGen = new GaussianGenerator(Vector3(.0), Vector3(.0), 5.0, 5.0, 1.0, .05, .0, .0, .0, 1.0, { .0, .0, .0, 1.0 });


	shootForce = new ForceGenerator();
	forces.push_back(shootForce);
	ball->registerForceGenerator(gravity);
}

void 
GameScene::processKey(unsigned char c, const physx::PxTransform* camera) {
	switch (c) {
	case 'c':
		toggleConfetti(nextConfettiActivation);
		nextConfettiActivation = !nextConfettiActivation;
		break;
	case 'f': {
		Vector3 forceDir = GetCamera()->getDir().getNormalized();
		Vector3 force = 800.0 * forceDir;
		shootForce->setForce(force);
		ball->setPosition(GetCamera()->getTransform().p);
		ball->registerForceGenerator(shootForce);
		ball->registerParticleGenerator(ballGen, 1);

		pGenToRemove.push({ ball, ballGen });
		forceToRemove.push({ ball, shootForce });
		break;
	}
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
