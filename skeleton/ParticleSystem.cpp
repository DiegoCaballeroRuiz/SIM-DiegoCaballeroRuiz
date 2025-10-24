#include "ParticleSystem.h"

#include "ParticleGen.h"
#include "ForceGenerator.h"
#include "Particle.hpp"

ParticleSystem::ParticleSystem() {

}

ParticleSystem::~ParticleSystem() {
	for (Particle* particle : particles)
		delete particle;
	particles.clear();

	for (genInfo info : particleGenerators)
		delete info.generator;
	particleGenerators.clear();

	for (ForceGenerator* generator : forceGenerators)
		delete generator;
	forceGenerators.clear();
}

void 
ParticleSystem::registerParticleGenerator(ParticleGenerator* gen, int nParticles) {
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
		std::vector<Particle*> newParticles = gen.generator->generate(gen.nParticles);
		particles.insert(particles.end(), newParticles.begin(), newParticles.end());
	}

	//Add force to particles
	for (ForceGenerator* generator : forceGenerators)
		for (Particle* particle : particles)
			generator->applyForce(particle);
	

	// Update the remaining particles
	for (Particle* particle : particles)
		particle->integrate(delta);
}