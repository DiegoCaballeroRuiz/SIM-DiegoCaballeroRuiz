#include "ParticleGenerator.h"
#include "Particle.hpp"

ParticleGenerator::ParticleGenerator(Vector3 position, Vector3 direction, double speed, double duration, double probGen, double mass)
	: position(Vector3(0.0)), offset(position), duration(duration), probGen(probGen), speed(speed), direction(direction), mass(mass)
{
}

ParticleGenerator::~ParticleGenerator() {}

std::vector<GameObject*> 
ParticleGenerator::generate(int nParticles) {
	std::vector<GameObject*> particles;

	for (int i = 0; i < nParticles; ++i) {
		auto particle = genParticle();
		if (particle != nullptr) particles.push_back(particle);
	}

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

Vector3 
ParticleGenerator::getOffset() {
	return offset;
}

void 
ParticleGenerator::setOffset(Vector3 newOffset) {
	offset = newOffset;
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
	
