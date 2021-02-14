#pragma once

#include <Windows.h>

constexpr auto VK_UNDEFINED = 0x07;
constexpr auto VK_Q = 0x51;
constexpr auto VK_D = 0x44;
constexpr auto VK_E = 0x45;

bool isPressed(int key) {
	return GetAsyncKeyState(key) & 0x8000;
}

int main() {
	const int wait = 15;
	bool running = true;

	INPUT releaseInputs[2];
	INPUT pressInputs[2];
	INPUT mouseInputs[2];
	INPUT levelInputs[1];
	INPUT releaseLevelInputs[1];

	ZeroMemory(mouseInputs, sizeof(mouseInputs));
	ZeroMemory(levelInputs, sizeof(levelInputs));
	ZeroMemory(releaseLevelInputs, sizeof(releaseLevelInputs));

	// Press the right mouse button.
	mouseInputs[0].type = INPUT_KEYBOARD;
	mouseInputs[0].ki.wVk = VK_RBUTTON;

	// Release the right mouse button.
	mouseInputs[1].type = INPUT_KEYBOARD;
	mouseInputs[1].ki.wVk = VK_RBUTTON;
	mouseInputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	// Press the E key.
	levelInputs[0].type = INPUT_KEYBOARD;
	levelInputs[0].ki.wVk = VK_E;

	// Release the E key.
	releaseLevelInputs[0].type = INPUT_KEYBOARD;
	releaseLevelInputs[0].ki.wVk = VK_E;
	releaseLevelInputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

	while (running) {
		Sleep(10);

		if (isPressed(VK_END)) {
			running = false;
		}

		if (isPressed(VK_XBUTTON1)) {
			ZeroMemory(releaseInputs, sizeof(releaseInputs));
			ZeroMemory(pressInputs, sizeof(pressInputs));

			// If we're already holding the key, we don't want to release it.
			const bool QAlreadyPressed = isPressed(VK_Q);
			const bool DAlreadyPressed = isPressed(VK_D);

			// Press the Q key if not already pressed.
			pressInputs[0].type = INPUT_KEYBOARD;
			pressInputs[0].ki.wVk = QAlreadyPressed ? VK_UNDEFINED : VK_Q;

			// Press the D key if not already pressed.
			pressInputs[1].type = INPUT_KEYBOARD;
			pressInputs[1].ki.wVk = DAlreadyPressed ? VK_UNDEFINED : VK_D;

			// Release the Q key if not already pressed.
			releaseInputs[0].type = INPUT_KEYBOARD;
			releaseInputs[0].ki.wVk = QAlreadyPressed ? VK_UNDEFINED : VK_Q;
			releaseInputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

			// Release the D key if not already pressed.
			releaseInputs[1].type = INPUT_KEYBOARD;
			releaseInputs[1].ki.wVk = DAlreadyPressed ? VK_UNDEFINED : VK_D;
			releaseInputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

			SendInput(ARRAYSIZE(pressInputs), pressInputs, sizeof(INPUT));

			Sleep(wait);

			SendInput(ARRAYSIZE(mouseInputs), mouseInputs, sizeof(INPUT));

			Sleep(wait);

			SendInput(ARRAYSIZE(releaseInputs), releaseInputs, sizeof(INPUT));
			SendInput(ARRAYSIZE(levelInputs), levelInputs, sizeof(INPUT));

			Sleep(wait * 2);

			SendInput(ARRAYSIZE(releaseLevelInputs), releaseLevelInputs, sizeof(INPUT));
		}
	}

	return 0;
}