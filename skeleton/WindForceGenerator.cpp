#include "WindForceGenerator.h"

#include "GameObject.h"

WindForceGenerator::WindForceGenerator(Vector3 direction, double speed, double force) 
	: ForceGenerator(direction * speed), direction(direction), windSpeed(speed), windStrength(force)
{

}
void 
WindForceGenerator::applyForce(GameObject* gObject) {
	
	double objectSpeedInWindAxis = gObject->getVelocity().dot(direction);
	double speedDiff = windSpeed - objectSpeedInWindAxis;
	Vector3 force = direction * speedDiff * windStrength;
	gObject->addForce(force);
}
