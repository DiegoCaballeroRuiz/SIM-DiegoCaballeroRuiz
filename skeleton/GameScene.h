#pragma once

#include "Scene.h"
#include <vector>

#include <queue>

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

	ForceGenerator* shootForce;
	ParticleSystem* ball;
	ParticleGenerator* ballGen;

	std::vector<ForceGenerator*> forces;
	bool nextConfettiActivation;

	std::queue<std::pair<ParticleSystem*, ForceGenerator*>> forceToRemove;
	std::queue<std::pair<ParticleSystem*, ParticleGenerator*>> pGenToRemove;

	void toggleConfetti(bool r);
	
public:
	GameScene();
	~GameScene();

	void integrate(double t) override;

	void start() override;
	void processKey(unsigned char c, const physx::PxTransform* camera) override;
};

