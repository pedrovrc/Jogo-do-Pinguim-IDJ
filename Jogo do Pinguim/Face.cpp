#include "Face.h"
#include "Sound.h"

Face::Face(GameObject& associated) {
	this->associated = associated;
	hitpoints = 30;
}

void Face::Damage(int damage) {
	hitpoints -= damage;
	if (hitpoints <= 0) {
		associated.RequestDelete();
		Sound* cpt = associated.GetComponent("Sound");
		if (cpt != nullptr) {
			cpt->Play(1);
		}
	}
}

void Face::Update(float dt) {

}

void Face::Render() {

}

bool Face::Is(string type) {
	if (type == "Face") return true;
	return false;
}
