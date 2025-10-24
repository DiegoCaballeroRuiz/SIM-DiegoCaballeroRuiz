#include "Scenes.h"
#include "GaussianGenerator.h"
#include "UniformGenerator.h"
#include "ForceGenerator.h"

Scene2::~Scene2() {}

void 
Scene2::integrate(double t) {
	pSys.update(t);
}

void 
Scene2::start() {
	pSys = ParticleSystem();

	UniformGenerator* uGen = new UniformGenerator(Vector3(-10, 0.0, 0.0), Vector3(1.0, 0.0, 0.0), 10.0, 1.0, 1.0, 5, 10.0, 6, 1.5, 1.5, {1.0, 0.0, 0.0, 1.0});
	GaussianGenerator* gGen = new GaussianGenerator(Vector3(10, 0.0, 0.0), Vector3(1.0, 0.0, 0.0), 10.0, 1.0, 1.0, 2, 10.0, 6, 1.5, 1.5, {0.0, 1.0, 1.0, 1.0});
	pSys.registerParticleGenerator(uGen, 1);
	pSys.registerParticleGenerator(gGen, 1);

	/*ForceGenerator* gravityGen = new ForceGenerator(Vector3(0, -10, 0));
	pSys.registerForceGenerator(gravityGen);*/
}

void 
Scene2::processKey(unsigned char c, const physx::PxTransform* camera) {
}