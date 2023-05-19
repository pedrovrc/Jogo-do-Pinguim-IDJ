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
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
			quitRequested = true;
		}

		// clique
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			mouseButton = event.button.button;
			UpdateKeyOrButtonMaps(mouseButton, event, "mouse");
		}

		// tecla
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
			key = event.key.keysym.sym;
			if (IsDirectional(key)) UpdateKeyOrButtonMaps(key, event, "keyboard");
			else if (event.key.repeat != 1) UpdateKeyOrButtonMaps(key, event, "keyboard");
		}
	}
}

bool InputManager::IsDirectional(int key) {
	if (key == LEFT_ARROW_KEY || key == RIGHT_ARROW_KEY
	   || key == UP_ARROW_KEY || key == DOWN_ARROW_KEY) return true;
	return false;
}

void InputManager::UpdateKeyOrButtonMaps(int index, SDL_Event event, string type) {
	if (type == "mouse") {
		mouseUpdate[index] = updateCounter;
		if (event.type == SDL_MOUSEBUTTONDOWN) mouseState[index] = true;
		if (event.type == SDL_MOUSEBUTTONUP) mouseState[index] = false;
	} else if (type == "keyboard") {
		keyUpdate[index] = updateCounter;
		if (event.type == SDL_KEYDOWN) keyState[index] = true;
		if (event.type == SDL_KEYUP) keyState[index] = false;
	} else {
		cout << "Invalid type selected. Use 'mouse' or 'keyboard' only." << endl;
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
