#include "GameObject.h"

GameObject::GameObject(Vector3 pos, double mass, physx::PxGeometry geo, Vector4 color, double lifeTime) 
	: pose(pos), lifetime(lifeTime), timeAlive(.0)
{
	renderItem = new RenderItem(CreateShape(geo), &pose, color);
}

GameObject::~GameObject() {
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void 
GameObject::integrate(double delta) {
	timeAlive += delta;
}
