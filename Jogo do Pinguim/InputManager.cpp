#include "InputManager.h"

InputManager& InputManager::GetInstance() {
	static InputManager manager;
	return manager;
}

InputManager::InputManager() {
	for (auto i : mouseState) {
		mouseState[i] = false;
	}
	for (auto i : mouseUpdate) {
		mouseUpdate[i] = 0;
	}
	quitRequested = false;
	updateCounter = 0;
	mouseX = 0;
	mouseY = 0;
}
