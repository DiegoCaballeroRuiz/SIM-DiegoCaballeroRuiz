#include "SolidSystem.h"
#include "ForceGenerator.h"

SolidSystem::SolidSystem(Vector3 pos)
	: uncappedSolids(true), pos(pos), maxSolids()
{
}

SolidSystem::SolidSystem(Vector3 pos, int maxSolids)
	: maxSolids(maxSolids), uncappedSolids(false), pos(pos)
{
}

SolidSystem::~SolidSystem() {
	for (auto solid : solids)
		solid->getScene()->removeActor(*solid);
	solids.clear();

	for (genInfo info : solidGenerators)
		delete info.generator;
	solidGenerators.clear();
}

void
SolidSystem::registerSolidGenerator(SolidGenerator* gen, int nSolids) {
	gen->setPos(gen->getOffset() + pos);
	solidGenerators.push_back({ gen, nSolids });
}

void
SolidSystem::deRegisterSolidGenerator(SolidGenerator* gen) {
	for (auto it = solidGenerators.begin(); it != solidGenerators.end();) {
		if (it->generator == gen) {
			it = solidGenerators.erase(it);
		}
		else ++it;
	}
}

void
SolidSystem::registerForceGenerator(ForceGenerator* gen) {
	forceGenerators.push_back(gen);
}

void
SolidSystem::deRegisterForceGenerator(ForceGenerator* gen) {
	for (auto it = forceGenerators.begin(); it != forceGenerators.end();) {
		if (*it == gen) {
			it = forceGenerators.erase(it);
		}
		else ++it;
	}
}

void
SolidSystem::update(double delta) {
	// Remove the dead solids
	//for (auto it = solids.begin(); it != solids.end();) {
	//	if (*it != nullptr) {
	//		if (!(*it)->isAlive()) {
	//			Particle* aux = *it;
	//			it = solids.erase(it);
	//			delete aux;
	//		}
	//		else ++it;
	//	}
	//	else it = solids.erase(it);
	//}

	// Generate new solids
	for (genInfo gen : solidGenerators) {
		gen.generator->setPos(gen.generator->getOffset() + pos);

		if (!uncappedSolids && gen.nParticles + solids.size() > maxSolids) continue;

		std::vector<physx::PxRigidBody*> newSolids = gen.generator->generate(gen.nSolids);
		solids.insert(solids.end(), newSolids.begin(), newSolids.end());
	}

	// Add force to solids
	for (ForceGenerator* generator : forceGenerators) {
		generator->update(delta);
		for (auto solid : solids)
			generator->applyForce(solid);
	}
}

std::vector<physx::PxRigidBody*>& 
SolidSystem::getSolids() {
	return solids;
}

Vector3
SolidSystem::getPosition() const {
	return pos;
}

void
SolidSystem::setPosition(Vector3 newPos) {
	pos = newPos;
}

