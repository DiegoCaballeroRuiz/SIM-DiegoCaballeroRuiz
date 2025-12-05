#pragma once

#include <vector>
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

class SolidGenerator;
class ForceGenerator;

class SolidSystem
{
protected:
	struct genInfo {
		SolidGenerator* generator;
		int nParticles;
	};

	std::vector<physx::PxRigidBody*> solids;
	std::vector<ForceGenerator*> forceGenerators;
	std::vector<genInfo> solidGenerators;

	int maxSolids;
	bool uncappedSolids;

	Vector3 pos;
public:
	SolidSystem(Vector3 pos);
	SolidSystem(Vector3 pos, int maxSolids);

	~SolidSystem();

	void registerSolidGenerator(SolidGenerator* gen, int nSolids);
	/// NO LO BORRA !!!!!!!!!!!!!!!!
	void deRegisterSolidGenerator(SolidGenerator* gen);

	void registerForceGenerator(ForceGenerator* gen);
	/// NO LO BORRA !!!!!!!!!!!!!!!!
	void deRegisterForceGenerator(ForceGenerator* gen);

	void update(double delta);

	std::vector<physx::PxRigidBody*>& getSolids();

	Vector3 getPosition() const;
	void setPosition(Vector3 newPos);
};

