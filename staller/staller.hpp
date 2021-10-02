#pragma once

#include <Windows.h>

class Staller {
public:
	void run();

private:
	enum VirtualKeys {
		AIR_ROLL_RIGHT = 0x45,
		AIR_ROLL_LEFT = 0x51,
		TURN_RIGHT = 0x44,
		JUMP = 0x02,

		VK_UNDEFINED = 0x07
	};

	static constexpr int WAIT = 15;

	bool running = true;

	INPUT releaseInputs[2];
	INPUT pressInputs[2];
	INPUT mouseInputs[2];
	INPUT levelInputs[1];
	INPUT releaseLevelInputs[1];

private:
	inline void sendInput(INPUT* input, int size) { SendInput(size, input, sizeof(INPUT)); }
	inline bool isPressed(int key) { return GetAsyncKeyState(key) & 0x8000; }
	inline void sleep(int time) { Sleep(time); }

	void initialize();
};