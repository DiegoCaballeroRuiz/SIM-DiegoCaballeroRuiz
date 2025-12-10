#include "ForceGenerator.h"
#include "GameObject.h"

ForceGenerator::ForceGenerator(Vector3 force, Vector3 pos) : force(force), position(pos), time(.0)
{
}

ForceGenerator::~ForceGenerator() {}

void 
ForceGenerator::applyForce(GameObject* gObject) {
	gObject->addForce(force);
}

void 
ForceGenerator::setForce(Vector3 newForce) {
	force = newForce;
}

void 
ForceGenerator::update(double dt) {
	time += dt;
}
