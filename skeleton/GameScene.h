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
class SpringForceGenerator;
class Player;
class ConstantAccelForceGenerator;
class GameObject;

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
	ParticleSystem* globalWind;
	ForceGenerator* windForce;
	ParticleGenerator* windGen;
	const double WIND_FORCE_MAGNITUDE = 1;

	//Rain
	ParticleSystem* rain;
	ParticleGenerator* rainGen;
	ForceGenerator* gravity;

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

	//Losing check
	const int LOSING_FLOOR_BOUNCES = 4;
	const double COLISION_CHECK_COOLDOWN = .5;

	int currentFloorBounces;
	double currentCheckCooldown;

	UserData wallData;
	UserData floorData;

	//Spectators
	std::vector<StaticSolid*> bleachers;
	ParticleSystem* people;
	SpringForceGenerator* backboneForce;
	ForceGenerator* excitementForce;
	const int PEOPLE_PER_BLEACHER = 4;

	//Methods
	void manageWheather(double dt);
	void createBleachers();
	void toggleConfetti(bool activate);
	void toggleWind(bool activate);
	void toggleRain(bool activate);

	//To not leave memory
	std::vector<GameObject*> wontDeleteItself;
	std::vector<ForceGenerator*> forces;
	std::vector<ParticleSystem*> systems;
public:
	GameScene(physx::PxScene* scene, physx::PxPhysics* physics);
	~GameScene();

	void integrate(double t) override;

	void start() override;
	void processKey(unsigned char c) override;
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) override;
};

