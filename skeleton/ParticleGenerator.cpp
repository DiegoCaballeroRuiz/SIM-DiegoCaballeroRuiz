#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3 position, Vector3 direction, double speed, double duration, double probGen, double mass)
	: position(position), duration(duration), probGen(probGen), speed(speed), direction(direction), mass(mass)
{
}

ParticleGenerator::~ParticleGenerator() {}

std::vector<Particle*> 
ParticleGenerator::generate(int nParticles) {
	std::vector<Particle*> particles;
	particles.assign(nParticles, nullptr);

	for (Particle*& particle : particles)
		particle = genParticle();

	return particles;
}

Vector3 
ParticleGenerator::getPos() {
	return position;
}

void 
ParticleGenerator::setPos(Vector3 newPos) {
	position = newPos;
}

double 
ParticleGenerator::getDuration() {
	return duration;
}

void 
ParticleGenerator::setDuration(double newDuration) {
	duration = newDuration;
}

double 
ParticleGenerator::getProbGen() {
	return probGen;
}

void 
ParticleGenerator::setProbGen(double newProb) {
	probGen = newProb;
}

double 
ParticleGenerator::getSpeed() {
	return speed;
}
void 
ParticleGenerator::setSpeed(double newSpeed) {
	speed = newSpeed;
}

Vector3 
ParticleGenerator::getDirection() {
	return direction;
}

void 
ParticleGenerator::setDirection(Vector3 newDir) {
	direction = newDir;
}
	
