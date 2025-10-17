#include "Scenes.h"
#include "Proyectile.h"
#include "GaussianGenerator.h"
#include "UniformGenerator.h"

void 
Scene1::integrate(double t) {
	for (auto p : proyectiles) {
		p->integrate(t);
	}
}

void 
Scene1::start() {
	balloon = { Vector3(), Vector3(.0, .5, .2), Vector3(0, 10, 5), Vector3(.0, .2, .1), .9, 1.2, Vector4(1.0, 1.0, 0.0, 1.0) };
	bullet = { Vector3(), Vector3(200, 0, 0), Vector3(25, 0, 0), Vector3(.0, .0, .0), .9, 2, Vector4(.0, .0, .0, 1.0) };
	tennisBall = { Vector3(), Vector3(90, 0, 0), Vector3(15, 0, 0), Vector3(.0, -9.8, .0), .9, 56, Vector4(.5, 1.0, 0.2, 1.0) };
}

Scene1::~Scene1() {
	for (auto p : proyectiles) {
		delete p;
	}
}

void 
Scene1::processKey(unsigned char c, const physx::PxTransform* camera) {
	proyectileInfo info;
	bool generate = true;
	switch (c) {
	case '1': {
		info = balloon;
		break;
	}

	case '2': {
		info = bullet;
		break;
	}

	case '3': {
		info = tennisBall;
		break;
	}
	default: 
		generate = false;
		break;
	}

	if (!generate) return;
	info.pos = camera->p;
	proyectiles.push_back(new Proyectile(info.pos, info.realVel, info.simulatedVel, info.initialAcceleration, info.damping, info.mass, info.color));
}


Scene2::~Scene2() {}

void 
Scene2::integrate(double t) {
	pSys.update(t);
}

void 
Scene2::start() {
	pSys = ParticleSystem();

	UniformGenerator* uGen = new UniformGenerator(Vector3(), Vector3(1.0, 0.0, 0.0), 25, 20, 1.0, 1.5, 1.5, 1.5, 1.5);
	pSys.registerParticleGenerator(uGen, 1);
}

void 
Scene2::processKey(unsigned char c, const physx::PxTransform* camera) {
}