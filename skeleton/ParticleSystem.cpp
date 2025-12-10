#include "ParticleSystem.h"

#include "ParticleGenerator.h"
#include "SolidGenerator.h"
#include "ForceGenerator.h"
#include "GameObject.h"
#include "Particle.hpp"
#include "Solid.h"

#include <cmath>

ParticleSystem::ParticleSystem(Vector3 pos) 
	: uncappedParticles(true), uncappedRange(true), pos(pos)
{
}

ParticleSystem::ParticleSystem(Vector3 pos, int maxParticles) 
	: maxParticles(maxParticles), uncappedParticles(false), pos(pos)
{ 
}

ParticleSystem::ParticleSystem(Vector3 pos, int maxParticles, double range)
	: maxParticles(maxParticles), uncappedParticles(false), pos(pos), range(range), uncappedRange(false)
{
}


ParticleSystem::ParticleSystem(Vector3 pos, double range)
	: pos(pos), range(range), uncappedRange(false) 
{
}

ParticleSystem::~ParticleSystem() {
	for (auto gObject : gObjects)
		delete gObject;
	gObjects.clear();

	for (pGenInfo info : particleGenerators)
		delete info.generator;
	particleGenerators.clear();
}

void 
ParticleSystem::registerParticleGenerator(ParticleGenerator* gen, int nParticles) {
	gen->setPos(gen->getOffset() + pos);
	particleGenerators.push_back({gen, nParticles});
}

void 
ParticleSystem::deRegisterParticleGenerator(ParticleGenerator* gen) {
	for (auto it = particleGenerators.begin(); it != particleGenerators.end();) {
		if (it->generator == gen) {
			it = particleGenerators.erase(it);
		}
		else ++it;
	}
}

void 
ParticleSystem::registerSolidGenerator(SolidGenerator* gen, int nParticles) {
	gen->setPos(gen->getOffset() + pos);
	solidGenerators.push_back({ gen, nParticles });
}

void 
ParticleSystem::deRegisterSolidGenerator(SolidGenerator* gen) {
	for (auto it = solidGenerators.begin(); it != solidGenerators.end();) {
		if (it->generator == gen) {
			it = solidGenerators.erase(it);
		}
		else ++it;
	}
}

void 
ParticleSystem::registerForceGenerator(ForceGenerator* gen) {
	forceGenerators.push_back(gen);
}

void 
ParticleSystem::deRegisterForceGenerator(ForceGenerator* gen) {
	for (auto it = forceGenerators.begin(); it != forceGenerators.end();) {
		if (*it == gen) {
			it = forceGenerators.erase(it);
		}
		else ++it;
	}
}

void 
ParticleSystem::update(double delta) {
	// Kill GameObjects outside AOE
	if (!uncappedRange) {
		for (auto gObject : gObjects) {
			double distance = 
				std::pow(pos.x - gObject->getTransform()->p.x, 2) + 
				std::pow(pos.y - gObject->getTransform()->p.y, 2) + 
				std::pow(pos.z - gObject->getTransform()->p.z, 2);

			if (distance > range) gObject->kill();
		}
	}

	// Remove the dead GameObjects
	for (auto it = gObjects.begin(); it != gObjects.end();) {
		if (*it != nullptr) {
			if (!(*it)->isAlive()) {
				auto aux = *it;
				it = gObjects.erase(it);
				delete aux;
			}
			else ++it;
		}
		else it = gObjects.erase(it);
	}

	// Generate new particles
	for (pGenInfo gen : particleGenerators) {
		gen.generator->setPos(gen.generator->getOffset() + pos);

		if (!uncappedParticles && gen.nParticles + gObjects.size() > maxParticles) continue;

		std::vector<GameObject*> newParticles = gen.generator->generate(gen.nParticles);
		gObjects.insert(gObjects.end(), newParticles.begin(), newParticles.end());
	}

	//Generate new solids
	for (sGenInfo gen : solidGenerators) {
		gen.generator->setPos(gen.generator->getOffset() + pos);

		if (!uncappedParticles && gen.nSolids + gObjects.size() > maxParticles) continue;

		std::vector<GameObject*> newSolids = gen.generator->generate(gen.nSolids);
		gObjects.insert(gObjects.end(), newSolids.begin(), newSolids.end());
	}

	// Add force to GameObjects
	for (ForceGenerator* generator : forceGenerators) {
		generator->update(delta);
		for (auto gObject : gObjects)
			generator->applyForce(gObject);
	}
	
	// Update the resulting GameObjects
	for (auto gObject : gObjects)
		gObject->integrate(delta);
}

Vector3 
ParticleSystem::getPosition() const {
	return pos;
}

void 
ParticleSystem::setPosition(Vector3 newPos) {
	pos = newPos;
}