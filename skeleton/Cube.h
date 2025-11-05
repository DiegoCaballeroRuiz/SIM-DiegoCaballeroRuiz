#pragma once

#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

class Cube
{
	RenderItem* renderItem;
	physx::PxTransform pose;
public:
	Cube(Vector3 pos = Vector3(0.0), Vector4 color = Vector4(1.0, 1.0, 1.0, 1.0), double hx = 1.0, double hy = 1.0, double hz = 1.0);
	~Cube();
};

