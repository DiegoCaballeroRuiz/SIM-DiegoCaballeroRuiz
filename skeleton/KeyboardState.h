#pragma once

//Keyboard abstraction singleton
class KeyboardState
{
	static KeyboardState* instance;
	static constexpr int CHAR_NUMBER = 128;

	bool keyboardState[CHAR_NUMBER];

	void initKeyboardState() {
		for (int i = 0; i < CHAR_NUMBER; ++i)
			keyboardState[i] = false;
	}

	explicit KeyboardState() { initKeyboardState(); }

public:
	static KeyboardState* Instance() {
		if (instance != nullptr) return instance;

		instance = new KeyboardState();
		return instance;
	}

	inline void setKeyDown(unsigned char key) { keyboardState[key] = true; }
	inline void setKeyUp(unsigned char key) { keyboardState[key] = false; }
	inline bool isKeyDown(unsigned char key) const { return keyboardState[key]; }
};

