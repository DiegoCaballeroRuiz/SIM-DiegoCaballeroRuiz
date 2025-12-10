#pragma once

#include "Scene.h"
#include <vector>

#include <queue>

class Cube;
class ParticleSystem;
class ParticleGenerator;
class SolidGenerator;
class Particle;
class ForceGenerator;
class GameScene : public Scene 
{
	Cube* floor;
	Cube* wall;
	Cube* wallLine;

	ParticleSystem* confetti;
	Particle* confettiCenter;
	std::vector<ParticleGenerator*> confettiGens;
	ForceGenerator* confettiForce;
	ForceGenerator* gravity;

	ForceGenerator* shootForce;
	ParticleSystem* ball;
	SolidGenerator* ballGen;
	ParticleGenerator* proyectileBallGen;

	ParticleSystem* wind;
	ForceGenerator* windForce;
	ParticleGenerator* windGen;
	bool nextWind;

	ParticleSystem* rain;
	ParticleGenerator* rainGen;
	bool nextRain;

	std::vector<ForceGenerator*> forces;
	bool nextConfettiActivation;

	std::queue<std::pair<ParticleSystem*, ForceGenerator*>> forceToRemove;
	std::queue<std::pair<ParticleSystem*, ParticleGenerator*>> pGenToRemove;
	std::queue<std::pair<ParticleSystem*, SolidGenerator*>> sGenToRemove;

	void toggleConfetti(bool activate);
	void toggleWind(bool activate);
	void toggleRain(bool activate);
	void processRemovals();
	const double SHOOT_FORCE = 800.0; //Fuerza en newtons de un golpe profesional de frontón
	
public:
	GameScene(physx::PxScene* scene, physx::PxPhysics* physics);
	~GameScene();

	void integrate(double t) override;

	void start() override;
	void processKey(unsigned char c, const physx::PxTransform* camera) override;
};

