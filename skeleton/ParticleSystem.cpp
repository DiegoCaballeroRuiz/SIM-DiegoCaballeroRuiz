#include "ParticleSystem.h"

#include "ParticleGenerator.h"
#include "ForceGenerator.h"
#include "Particle.hpp"

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
	for (Particle* particle : particles)
		delete particle;
	particles.clear();

	for (genInfo info : particleGenerators)
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
	// Kill particles outside AOE
	if (!uncappedRange) {
		for (Particle* particle : particles) {
			double distance = 
				std::pow(pos.x - particle->getTransform()->p.x, 2) + 
				std::pow(pos.y - particle->getTransform()->p.y, 2) + 
				std::pow(pos.z - particle->getTransform()->p.z, 2);

			if (distance > range) particle->kill();
		}
	}

	// Remove the dead particles
	for (auto it = particles.begin(); it != particles.end();) {
		if (*it != nullptr) {
			if (!(*it)->isAlive()) {
				Particle* aux = *it;
				it = particles.erase(it);
				delete aux;
			}
			else ++it;
		}
		else it = particles.erase(it);
	}

	// Generate new particles
	for (genInfo gen : particleGenerators) {
		gen.generator->setPos(gen.generator->getOffset() + pos);

		if (!uncappedParticles && gen.nParticles + particles.size() > maxParticles) continue;

		std::vector<Particle*> newParticles = gen.generator->generate(gen.nParticles);
		particles.insert(particles.end(), newParticles.begin(), newParticles.end());
	}

	// Add force to particles
	for (ForceGenerator* generator : forceGenerators) {
		generator->update(delta);
		for (Particle* particle : particles)
			generator->applyForce(particle);
	}
	
	// Update the resulting particles
	for (Particle* particle : particles)
		particle->integrate(delta);
}

std::vector<Particle*>&
ParticleSystem::getParticles() {
	return particles;
}

Vector3 
ParticleSystem::getPosition() const {
	return pos;
}

void 
ParticleSystem::setPosition(Vector3 newPos) {
	pos = newPos;
}