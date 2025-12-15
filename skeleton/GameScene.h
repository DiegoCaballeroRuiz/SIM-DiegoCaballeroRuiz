#pragma once

#include "Scene.h"
#include <vector>

#include <queue>
#include <random>

#include "UserData.h"



class Cube;
class ParticleSystem;
class ParticleGenerator;
class SolidGenerator;
class StaticSolid;
class Particle;
class ForceGenerator;
class Player;

class GameScene : public Scene 
{
	//Scenery
	StaticSolid* floor;
	StaticSolid* hitWall;
	StaticSolid* rightWall;
	StaticSolid* backWall;
	StaticSolid* leftWall;
	StaticSolid* wallLine;

	//Confetti
	ParticleSystem* confetti;
	Particle* confettiCenter;
	std::vector<ParticleGenerator*> confettiGens;
	ForceGenerator* confettiForce;
	bool nextConfettiActivation;

	//Global wind
	ParticleSystem* wind;
	ForceGenerator* windForce;
	ParticleGenerator* windGen;

	//Rain
	ParticleSystem* rain;
	ParticleGenerator* rainGen;

	//Force management
	ForceGenerator* gravity;
	std::vector<ForceGenerator*> forces;

	//Toggles
	void toggleConfetti(bool activate);
	void toggleWind(bool activate);
	void toggleRain(bool activate);

	//Player
	Player* rafaNadal;

	//Randomness
	std::mt19937 rng;
	std::uniform_real_distribution<double> wheatherEventDelayGenerator;
	std::uniform_real_distribution<double> chance;

	const double MIN_NEXT_WHEATHER_DELAY = 20.;
	const double MAX_NEXT_WHEATHER_DELAY = 50.;
	const double RAIN_CHANCE = .5;

	double timeUntilNextWheatherEvent;
	bool inWheatherEvent;

	//Losing ceck
	const int LOSING_FLOOR_BOUNCES = 4;
	int currentFloorBounces;
	UserData wallData;
	UserData floorData;

	void manageWheather(double dt);
public:
	GameScene(physx::PxScene* scene, physx::PxPhysics* physics);
	~GameScene();

	void integrate(double t) override;

	void start() override;
	void processKey(unsigned char c) override;
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) override;
};

