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
