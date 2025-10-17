#include "ParticleSystem.h"

#include "ParticleGen.h"
#include "Particle.hpp"

ParticleSystem::ParticleSystem() {

}

ParticleSystem::~ParticleSystem() {
	for (Particle* particle : particles)
		delete particle;
	particles.clear();

	for (genInfo info : generators)
		delete info.generator;
	generators.clear();
}

void 
ParticleSystem::registerParticleGenerator(ParticleGenerator* gen, int nParticles) {
	generators.push_back({gen, nParticles});
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
	for (genInfo gen : generators) {
		std::vector<Particle*> newParticles = gen.generator->generate(gen.nParticles);
		particles.insert(particles.end(), newParticles.begin(), newParticles.end());
	}

	// Update the remaining particles
	for (Particle* particle : particles)
		particle->integrate(delta);
}