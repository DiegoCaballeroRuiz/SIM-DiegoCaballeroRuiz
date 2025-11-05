#include "GameScene.h"

#include "Cube.h"
#include "UniformGenerator.h"
#include "ExplosionForceGenerator.h"
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
}

void 
GameScene::integrate(double t) {
	confetti->update(t);
}

void 
GameScene::start() {
	floor = new Cube(Vector3(0), { 0.8, 0.8, 0.25, 1.0 }, 1000.0, .2, 1000.0);
	wall = new Cube(Vector3(0.0, 100.0, -100), { 0.0, 0.8, 0.2, 1.0 }, 1000.0, 200.0, 1.0);
	wallLine = new Cube(Vector3(0.0, 10, -100), { .0, .0, .0, 1.0 }, 1000.0, 5, 1.5);

	confetti = new ParticleSystem(Vector3(0, 100.0, 0));
	
	UniformGenerator* confetti1 = new UniformGenerator(confetti->getPosition(), Vector3(.0), 5.0, 10.0, 1.0, 1.0, 1.0, .0, .0, 1.0, { 1.0, 0.0, 0.0, 1.0 });
	UniformGenerator* confetti2 = new UniformGenerator(confetti->getPosition(), Vector3(.0), 5.0, 10.0, 1.0, 1.0, 1.0, .0, .0, 1.0, { .0, 1.0, 0.0, 1.0 });
	UniformGenerator* confetti3 = new UniformGenerator(confetti->getPosition(), Vector3(.0), 5.0, 10.0, 1.0, 1.0, 1.0, .0, .0, 1.0, { .0, .0, 1.0, 1.0 });

	confettiGens = { confetti1, confetti2, confetti3 };
	confettiForce = new ExplosionForceGenerator(Vector3(100.0, 0.0, 0.0), confetti->getPosition(), 5.0);
	gravity = new ForceGenerator(Vector3(0.0, -10.0, 0.0));
	forces.push_back(gravity);
	confetti->registerForceGenerator(gravity);

	Particle* center = new Particle(confetti->getPosition(), Vector3(0.0), 0.9, 1, Vector4(1.0, 0.0, 1.0, 1.0));
}

void 
GameScene::processKey(unsigned char c, const physx::PxTransform* camera) {
	switch (c) {
	case 'c':
		toggleConfetti(nextConfettiActivation);
		nextConfettiActivation = !nextConfettiActivation;
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
