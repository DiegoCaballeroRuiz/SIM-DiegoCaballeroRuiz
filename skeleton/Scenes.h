#pragma once
#include <vector>
#include "Scene.h"
#include "core.hpp"

class Proyectile;
class Scene1 : public Scene {
private:
	std::vector<Proyectile*> proyectiles;

	struct proyectileInfo {
		Vector3 pos;
		Vector3 realVel;
		Vector3 simulatedVel;
		Vector3 initialAcceleration;
		double damping;
		double mass;
		Vector4 color;
	};

	proyectileInfo balloon;
	proyectileInfo bullet;
	proyectileInfo tennisBall;


public:
	Scene1() : Scene() {}
	~Scene1();
	void integrate(double t) override;
	void start() override;
	void processKey(unsigned char c, const physx::PxTransform* camera) override;
};