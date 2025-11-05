#include "Cube.h"

Cube::Cube(Vector3 pos, Vector4 color, double hx, double hy, double hz) 
	: pose(pos) 
{
	renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(hx, hy, hz)), &pose, color);
}

Cube::~Cube() {
	DeregisterRenderItem(renderItem);
	delete renderItem;
}
