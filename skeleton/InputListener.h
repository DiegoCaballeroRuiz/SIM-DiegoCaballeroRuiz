#pragma once
class InputListener
{
public:
	virtual void processKey(unsigned char c) = 0;
	virtual ~InputListener() {}
};

