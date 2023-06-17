#include "PenguinCannon.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Game.h"
#include "GeneralFunctions.h"
#include "Camera.h"

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody) : Component(associated) {
	pbody = penguinBody;
	angle = 0;
	Sprite* sprcannon = new Sprite(associated, "img/cubngun.png");
	associated.AddComponent((Component*)sprcannon);
	associated.box.SetCenterPosition(pbody.lock().get()->box.GetCenter());
}

void PenguinCannon::Update(float dt) {
	if (pbody.expired()) {
		associated.RequestDelete();
		return;
	}
	InputManager* input = &InputManager::GetInstance();

	associated.box.SetCenterPosition(pbody.lock().get()->box.GetCenter());
	Vec2 mousePos = input->GetMousePoint() + Camera::pos;
	Vec2 direction = mousePos - associated.box.GetCenter();
	angle = direction.GetAngle();
	associated.angleDeg  = Rad2Deg(angle);

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
	Vec2 offset = *new Vec2(BULLET_OFFSET, 0);
	Vec2 bulletPos = associated.box.GetCenter() + offset.GetRotated(Deg2Rad(associated.angleDeg));
	bulletGO->box.SetPosition(bulletPos);
	Component* bullet = new Bullet( *bulletGO,
									Deg2Rad(associated.angleDeg),
									PENGUIN_DMG,
									PENGUIN_MAX_DISTANCE,
									"img/minionbullet2.png",
									3,
									100 );
	bulletGO->AddComponent(bullet);
	Game::GetInstance().GetState().AddObject(bulletGO);
	associated.started = true;
}
