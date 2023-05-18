#include "Face.h"
#include "Sound.h"

Face::Face(GameObject& associated) : Component(associated) {
	hitpoints = 30;
}

void Face::Damage(int damage) {
	hitpoints -= damage;
	if (hitpoints <= 0) {
		//associated.RequestDelete();
		Sound* cpt = (Sound*)associated.GetComponent("Sound");
		if (cpt != nullptr) {
			cpt->Play(1);
		}
	}
}

void Face::Update(float dt) {
	InputManager* input = &(InputManager::GetInstance());
	if (input->MousePress(LEFT_MOUSE_BUTTON)) {
		Vec2 mouse;
		mouse.x = input->GetMouseX();
		mouse.y = input->GetMouseY();
		if (associated.box.IsInside(mouse)) {
			Damage(rand() % 10 + 10);
		}
	}

	if (hitpoints <= 0) {
		Sound* cpt = (Sound*)associated.GetComponent("Sound");
		if (Mix_Playing(cpt->GetChannel()) == false) {
			associated.RequestDelete();
		}
	}
}

void Face::Render() {

}

bool Face::Is(string type) {
	if (type == "Face") return true;
	return false;
}

int Face::GetHP() {
	return hitpoints;
}
