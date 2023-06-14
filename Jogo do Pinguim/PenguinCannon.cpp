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

	cout << "PenguinBody box: "; pbody.lock().get()->box.GetPos().Print();
	cout << "PenguinCannon box before: "; associated.box.GetPos().Print();

	associated.box.SetCenterPosition(pbody.lock().get()->box.GetCenter());
	Vec2 direction = input->GetMousePoint() - associated.box.GetCenter(); // incluir camera?
	angle = direction.GetAngle();
	cout << "Angle = " << angle << endl;
	associated.angleDeg += 1;

	cout << "PenguinCannon box after: "; associated.box.GetPos().Print();

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
	bulletGO->box.SetPosition(associated.box.GetCenter());
	Component* bullet = new Bullet( *bulletGO,
									associated.angleDeg,
									PENGUIN_DMG,
									PENGUIN_MAX_DISTANCE,
									"img/minionbullet2.png",
									3,
									100 );
	bulletGO->AddComponent(bullet);
	Game::GetInstance().GetState().AddObject(bulletGO);
	associated.started = true;
}
