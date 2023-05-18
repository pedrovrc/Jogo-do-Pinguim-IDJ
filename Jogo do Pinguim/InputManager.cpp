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

InputManager::~InputManager() {

}

void InputManager::Update() {
	SDL_Event event;
	int mouseButton, key;

	SDL_GetMouseState(&mouseX, &mouseY);
	quitRequested = false;
	updateCounter++;

	while (SDL_PollEvent(&event)) {
		// saida
		if (event.type == SDL_QUIT) quitRequested = true;

		// clique
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			mouseButton = event.button.button;
			mouseUpdate[mouseButton] = updateCounter;

			if (event.type == SDL_MOUSEBUTTONDOWN) {
				mouseState[mouseButton] = true;
			}

			if (event.type == SDL_MOUSEBUTTONUP) {
				mouseState[mouseButton] = false;
			}
		}

		// tecla
		if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat != 1) {
			key = event.key.keysym.sym;
			keyUpdate[key] = updateCounter;

			if (event.type == SDL_KEYDOWN) {
				keyState[key] = true;
			}

			if (event.type == SDL_KEYUP) {
				keyState[key] = false;
			}
		}
	}
}

bool InputManager::KeyPress (int key) {
	if (keyState[key] == true && keyUpdate[key] == updateCounter) return true;
	else return false;
}

bool InputManager::KeyRelease (int key) {
	if (keyState[key] == false && keyUpdate[key] == updateCounter) return true;
	else return false;
}

bool InputManager::IsKeyDown (int key) {
	if (keyState[key] == true) return true;
	else return false;
}

bool InputManager::MousePress (int button) {
	if (mouseState[button] == true && mouseUpdate[button] == updateCounter) return true;
	else return false;
}

bool InputManager::MouseRelease (int button) {
	if (mouseState[button] == false && mouseUpdate[button] == updateCounter) return true;
	else return false;
}

bool InputManager::IsMouseDown (int button) {
	if (mouseState[button] == true) return true;
	else return false;
}

int InputManager::GetMouseX() {
	return mouseX;
}

int InputManager::GetMouseY() {
	return mouseY;
}

bool InputManager::QuitRequested() {
	return quitRequested;
}
