#pragma once

#include "ForceGenerator.h"
#include <unordered_map>

class SpringForceGenerator : public ForceGenerator {	
protected:
	double k;
	double restingLength;
	std::unordered_map<GameObject*, GameObject*> anchors;
public:
	SpringForceGenerator(double k, double restingLength);
	virtual ~SpringForceGenerator();

	virtual void applyForce(GameObject* gObject) override;

	void attachParticle(GameObject* affected, GameObject* anchor);

	void setK(double k);
	double getK() const;
};