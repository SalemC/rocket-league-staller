#pragma once

#include "staller.hpp"

void Staller::initialize() {
	ZeroMemory(this->mouseInputs, sizeof(this->mouseInputs));
	ZeroMemory(this->levelInputs, sizeof(this->levelInputs));
	ZeroMemory(this->releaseLevelInputs, sizeof(this->releaseLevelInputs));

	// Press the jump button.
	mouseInputs[0].type = INPUT_KEYBOARD;
	mouseInputs[0].ki.wVk = Staller::JUMP;

	// Release the jump button.
	mouseInputs[1].type = INPUT_KEYBOARD;
	mouseInputs[1].ki.wVk = Staller::JUMP;
	mouseInputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	// Press the air roll right key.
	levelInputs[0].type = INPUT_KEYBOARD;
	levelInputs[0].ki.wVk = Staller::AIR_ROLL_RIGHT;

	// Release the air roll right key.
	releaseLevelInputs[0].type = INPUT_KEYBOARD;
	releaseLevelInputs[0].ki.wVk = Staller::AIR_ROLL_RIGHT;
	releaseLevelInputs[0].ki.dwFlags = KEYEVENTF_KEYUP;
}

void Staller::run() {
	this->initialize();

	while (this->running) {
		if (this->isPressed(VK_END)) running = false;

		this->sleep(10);

		if (!this->isPressed(VK_XBUTTON1)) continue;

		ZeroMemory(this->releaseInputs, sizeof(this->releaseInputs));
		ZeroMemory(this->pressInputs, sizeof(this->pressInputs));

		// If we're already holding the key, we don't want to release it.
		const bool airRollLeftAlreadyPressed = this->isPressed(Staller::AIR_ROLL_LEFT);
		const bool turnRightAlreadyPressed = this->isPressed(Staller::TURN_RIGHT);

		// Press the air roll left key if not already pressed.
		this->pressInputs[0].type = INPUT_KEYBOARD;
		this->pressInputs[0].ki.wVk = airRollLeftAlreadyPressed ? Staller::VK_UNDEFINED : Staller::AIR_ROLL_LEFT;

		// Press the turn right key if not already pressed.
		this->pressInputs[1].type = INPUT_KEYBOARD;
		this->pressInputs[1].ki.wVk = turnRightAlreadyPressed ? Staller::VK_UNDEFINED : Staller::TURN_RIGHT;

		// Release the air roll left key if not already pressed.
		this->releaseInputs[0].type = INPUT_KEYBOARD;
		this->releaseInputs[0].ki.wVk = airRollLeftAlreadyPressed ? Staller::VK_UNDEFINED : Staller::AIR_ROLL_LEFT;
		this->releaseInputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

		// Release the turn right key if not already pressed.
		this->releaseInputs[1].type = INPUT_KEYBOARD;
		this->releaseInputs[1].ki.wVk = turnRightAlreadyPressed ? Staller::VK_UNDEFINED : Staller::TURN_RIGHT;
		this->releaseInputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

		this->sendInput(pressInputs, ARRAYSIZE(pressInputs));

		this->sleep(Staller::WAIT);

		this->sendInput(mouseInputs, ARRAYSIZE(mouseInputs));

		this->sleep(Staller::WAIT);

		this->sendInput(releaseInputs, ARRAYSIZE(releaseInputs));
		this->sendInput(levelInputs, ARRAYSIZE(levelInputs));

		this->sleep(Staller::WAIT * 2);

		this->sendInput(releaseLevelInputs, ARRAYSIZE(releaseLevelInputs));
	}
}