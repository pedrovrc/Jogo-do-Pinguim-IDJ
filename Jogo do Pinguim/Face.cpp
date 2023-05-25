#include "Face.h"
#include "Sound.h"
#include "Camera.h"

#define HP_VALUE 30

Face::Face(GameObject& associated) : Component(associated) {
	hitpoints = HP_VALUE;
}

/*
 * void Face::Update(float dt)
 *
 * Checa se objeto foi atingido no último frame e aplica dano em caso afirmativo.
 * Também checa se objeto está vivo ou não, requisitando remoção em caso afirmativo.
 */
void Face::Update(float dt) {
	InputManager* input = &(InputManager::GetInstance());
	if (hitpoints <= 0) {
		Sound* cpt = (Sound*)associated.GetComponent("Sound");
		if (Mix_Playing(cpt->GetChannel()) == false) {
			associated.RequestDelete();
		}
		return;
	}

	if (input->MousePress(LEFT_MOUSE_BUTTON)) {
		Vec2 mouse;
		mouse.x = input->GetMouseX() + Camera::pos.x;
		mouse.y = input->GetMouseY() + Camera::pos.y;
		if (associated.box.IsInside(mouse)) {
			Damage(rand() % 10 + 10);
		}
	}
}

/*
 * void Face::Damage(int damage)
 *
 * Aplica dano recebido (subtrai de hitpoints).
 */
void Face::Damage(int damage) {
	hitpoints -= damage;
	if (hitpoints <= 0) {
		Sound* cpt = (Sound*)associated.GetComponent("Sound");
		if (cpt != nullptr) {
			cpt->Play(1);
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
