#pragma once

enum whoami {
	OTHER,
	BALL,
	WALL,
	FLOOR
};

struct UserData {
	whoami identity;
	void* object;
};
