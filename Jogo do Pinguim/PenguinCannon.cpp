#include "PenguinCannon.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Game.h"

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody) : Component(associated) {
	pbody = penguinBody;
	angle = 0;
	Sprite* spr = new Sprite(associated, "img/cubngun.png");
	associated.AddComponent((Component*)spr);
}

void PenguinCannon::Update(float dt) {
	if (pbody.expired()) {
		associated.RequestDelete();
		return;
	}
	InputManager* input = &InputManager::GetInstance();

	associated.box.SetCenterPosition(pbody.lock().get()->box.GetCenter());
	associated.angleDeg = (associated.box.GetCenter() - input->GetMousePoint()).GetAngle() * 180/M_PI;

	if (input->MousePress(LEFT_MOUSE_BUTTON)) Shoot();
}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(string type) {
	if (type == "PenguinCannon") return true;
	return false;
}

void PenguinCannon::Start() {

}

void PenguinCannon::Shoot() {
	GameObject* bulletGO = new GameObject();
	bulletGO->box.MoveThis(associated.box.GetCenter());
	Component* bullet = new Bullet( *bulletGO,
									associated.angleDeg,
									BULLET_DMG,
									BULLET_MAX_DISTANCE,
									"img/minionbullet2.png",
									3,
									100 );
	bulletGO->AddComponent(bullet);
	Game::GetInstance().GetState().AddObject(bulletGO);
}
