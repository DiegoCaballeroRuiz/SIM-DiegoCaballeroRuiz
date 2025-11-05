#include "Scenes.h"
#include "GaussianGenerator.h"
#include "UniformGenerator.h"
#include "ForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "ParticleSystem.h"

Scene2::Scene2() : Scene()
{

}


Scene2::~Scene2() {
	delete pSys;
}

void 
Scene2::integrate(double t) {
	pSys->update(t);
}

void 
Scene2::start() {
	pSys = new ParticleSystem(Vector3(0.0));

	UniformGenerator* uGen = new UniformGenerator(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), 10.0, 100.0, 1.0, 1.0, 1.0, 3.0, .0, 3.0, {1.0, 1.0, 0.0, 1.0});
	//GaussianGenerator* gGen = new GaussianGenerator(Vector3(10, 0.0, 0.0), Vector3(1.0, 0.0, 0.0), 10.0, 1.0, 1.0, 2, 10.0, 6, 1.5, 1.5, {0.0, 1.0, 1.0, 1.0});
	pSys->registerParticleGenerator(uGen, 1);
	//pSys.registerParticleGenerator(gGen, 1);

	ForceGenerator* explosionGen = new ExplosionForceGenerator(Vector3(10, 0, 0), Vector3(0), 2);
	pSys->registerForceGenerator(explosionGen);

	ForceGenerator* gravityGen = new ForceGenerator(Vector3(0.0, -10.0, 0.0));
	pSys->registerForceGenerator(gravityGen);
}

void 
Scene2::processKey(unsigned char c, const physx::PxTransform* camera) {
}