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
	/*int lastToDelete = particles.size();
	int n = particles.size();
	for (int i = 0; i < n; ++i) {
		if (particles[i]->isAlive()) continue;

		lastToDelete--;
		Particle* temp = particles[lastToDelete];
		particles[lastToDelete] = particles[i];
		particles[i] = particles[lastToDelete];
		n--;
	}

	int deleted = 0;
	for (int i = lastToDelete; i < particles.size(); ++i) {
		delete particles[i];
		deleted++;
	}
	particles.resize(particles.size() - deleted);*/

	// Generate new particles
	for (genInfo gen : generators) {
		auto newParticles = gen.generator->generate(gen.nParticles);
		particles.insert(particles.end(), newParticles.begin(), newParticles.end());
	}

	// Update the remaining particles
	for (Particle* particle : particles)
		particle->integrate(delta);
}