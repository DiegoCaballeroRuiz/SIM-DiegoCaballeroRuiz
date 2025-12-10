#include "SpringsScene.h"

#include "ParticleSystem.h"
#include "SpringForceGenerator.h"
#include "ElasticForceGenerator.h"
#include "Particle.hpp"
#include "GravityForceGenerator.h"

SpringsScene::SpringsScene(physx::PxScene* scene, physx::PxPhysics* physics) : Scene(scene, physics) {}

SpringsScene::~SpringsScene() {
	delete pSys;
	delete springGen;
	delete gravity;
}

void 
SpringsScene::integrate(double t) {
	pSys->update(t);
}

void 
SpringsScene::start() {
	pSys = new ParticleSystem({ .0, .0, .0 });
	springGen = new ElasticForceGenerator(10.0, 5.0);

	anchor = new Particle({ .0, .0, .0 }, { .0, .0, .0 }, .9, 1);
	Particle* affected = new Particle({ 1.0, -1.0, .0 }, { .0, .0, .0 }, .9, 1);
	Particle* affected2 = new Particle({ -1.0, -1.0, .0 }, { .0, .0, .0 }, .9, 1);

	springGen->attachParticle(affected, anchor);
	springGen->attachParticle(affected2, anchor);
	springGen->attachParticle(affected, affected2);
	springGen->attachParticle(affected2, affected);

	gravity = new GravityForceGenerator(9.8);

	pSys->getObjects().push_back(affected);
	pSys->getObjects().push_back(affected2);
	pSys->getObjects().push_back(anchor);

	pSys->registerForceGenerator(springGen);
	//pSys->registerForceGenerator(gravity);
}

void 
SpringsScene::processKey(unsigned char c, const physx::PxTransform* camera) {
	switch (c) {
	case 'k':
		springGen->setK(springGen->getK() + 10);
		break;
	case 'l':
		springGen->setK(springGen->getK() - 10);
		break;
	case 't':
		toggleSpring(nextSpringActivation);
		nextSpringActivation = !nextSpringActivation;
		break;
	}
}

void 
SpringsScene::toggleSpring(bool activate) {
	if (activate) pSys->registerForceGenerator(springGen);
	else pSys->deRegisterForceGenerator(springGen);
}

