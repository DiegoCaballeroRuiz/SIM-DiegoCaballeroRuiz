#include "GameObject.h"

GameObject::GameObject(Vector4 color, double lifeTime) 
	: lifetime(lifeTime), timeAlive(.0), shape(shape)
{
}

GameObject::~GameObject() {
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void 
GameObject::integrate(double delta) {
	timeAlive += delta;
}
