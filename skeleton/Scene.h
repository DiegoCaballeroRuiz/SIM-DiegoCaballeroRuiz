#pragma once

namespace physx {
	class PxTransform;
}

class Scene
{
public:
	Scene();
	virtual void integrate(double t) = 0;

	virtual void start() = 0;
	virtual ~Scene() = 0;
	virtual void processKey(unsigned char c, const physx::PxTransform* camera) = 0;
protected:
};

