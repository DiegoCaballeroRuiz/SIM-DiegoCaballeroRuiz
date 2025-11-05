#pragma once

#include "Scene.h"
#include <vector>

class Cube;
class ParticleSystem;
class ParticleGenerator;
class ForceGenerator;
class GameScene : public Scene 
{
	Cube* floor;
	Cube* wall;
	Cube* wallLine;

	ParticleSystem* confetti;
	std::vector<ParticleGenerator*> confettiGens;
	ForceGenerator* confettiForce;
	ForceGenerator* gravity;

	std::vector<ForceGenerator*> forces;
	bool nextConfettiActivation;

	void toggleConfetti(bool r);
	
public:
	GameScene();
	~GameScene();

	void integrate(double t) override;

	void start() override;
	void processKey(unsigned char c, const physx::PxTransform* camera) override;
};

