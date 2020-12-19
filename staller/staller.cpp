#include <Windows.h>
#include <iostream>

constexpr auto VK_UNDEFINED = 0x07;
constexpr auto VK_Q = 0x51;
constexpr auto VK_D = 0x44;
constexpr auto VK_E = 0x45;

bool isPressed(int key) {
	return GetAsyncKeyState(key) & 0x0001;
}

int getKeyboardKey(int index) {
	switch (index) {
		case (0): {
			return VK_Q;
		}

		case (1): {
			return VK_D;
		}

		default: {
			return VK_UNDEFINED;
		}
	}
}

int main() {
	const auto wait = 15;
	auto running = true;

	INPUT initialInputs[2];
	INPUT finalInputs[2];
	INPUT mouseInputs[2];

	INPUT postInputs[1];
	INPUT postPostInputs[1];

	ZeroMemory(initialInputs, sizeof(initialInputs));
	ZeroMemory(finalInputs, sizeof(finalInputs));
	ZeroMemory(mouseInputs, sizeof(mouseInputs));
	ZeroMemory(postInputs, sizeof(postInputs));
	ZeroMemory(postPostInputs, sizeof(postPostInputs));

	for (auto i = 0; i < 2; i += 1) {
		auto key = getKeyboardKey(i);

		initialInputs[i].type = INPUT_KEYBOARD;
		initialInputs[i].ki.wVk = getKeyboardKey(i);

		finalInputs[i].type = INPUT_KEYBOARD;
		finalInputs[i].ki.wVk = getKeyboardKey(i);
		finalInputs[i].ki.dwFlags = KEYEVENTF_KEYUP;

		if (i == 0 || i == 1) {
			mouseInputs[i].type = INPUT_KEYBOARD;
			mouseInputs[i].ki.wVk = VK_RBUTTON;

			if (i == 1) {
				mouseInputs[i].ki.dwFlags = KEYEVENTF_KEYUP;
			}
		}
	}

	postInputs[0].type = INPUT_KEYBOARD;
	postInputs[0].ki.wVk = VK_E;

	postPostInputs[0].type = INPUT_KEYBOARD;
	postPostInputs[0].ki.wVk = VK_E;
	postPostInputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

	while (running) {
		Sleep(10);

		if (isPressed(VK_END)) {
			running = false;
		}

		if (isPressed(VK_XBUTTON1)) {
			SendInput(ARRAYSIZE(initialInputs), initialInputs, sizeof(INPUT));

			Sleep(wait);

			SendInput(ARRAYSIZE(mouseInputs), mouseInputs, sizeof(INPUT));

			Sleep(wait);

			SendInput(ARRAYSIZE(finalInputs), finalInputs, sizeof(INPUT));

			Sleep(wait);

			SendInput(ARRAYSIZE(postInputs), postInputs, sizeof(INPUT));
			
			Sleep(wait * 2);

			SendInput(ARRAYSIZE(postPostInputs), postPostInputs, sizeof(INPUT));
		}
	}

	return 0;
}