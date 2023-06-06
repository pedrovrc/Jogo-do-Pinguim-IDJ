#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"

#define ANG_VELOC M_PI/60
#define BULLET_DMG 10
#define BULLET_MAX_DISTANCE 1000

Minion::Minion(GameObject& associated,
		weak_ptr<GameObject> alienCenterArg,
		float arcOffsetDeg) : Component(associated) {
	Component* img = new Sprite(associated, "img/minion.png");
	associated.AddComponent(img);
	alienCenter = alienCenterArg.lock().get();

	// tratamento de entrada
	if (arcOffsetDeg < 0) arcOffsetDeg = -arcOffsetDeg;
	if (arcOffsetDeg > 360) arcOffsetDeg = (int)arcOffsetDeg % 360;
	arc = arcOffsetDeg * M_PI/180;

	//calcular primeiro valor da box
	Vec2 offset;
	offset.Set(200,0);
	offset.RotateThis(arc);
	offset += alienCenter->box.GetCenter();
	offset -= *new Vec2(associated.box.w/2, associated.box.h/2);

	// potencial problema
	associated.box.SetPosition(offset);
}

void Minion::Start() {

}

void Minion::Update(float dt) {
	if (alienCenter == nullptr) {
		associated.RequestDelete();
		return;
	}
	Vec2 offset;
	offset.Set(200,0);
	offset.RotateThis(arc);
	offset += alienCenter->box.GetCenter();
	offset -= *new Vec2(associated.box.w/2, associated.box.h/2);

	// potencial problema
	associated.box.SetPosition(offset);

	arc += ANG_VELOC;
	if (arc >= 2.0f * M_PI) arc = 0;
}

void Minion::Render() {

}

bool Minion::Is(string type) {
	if(type == "Minion") return true;
	return false;
}

void Minion::Shoot(Vec2 target) {
	GameObject* bulletGO = new GameObject();
	bulletGO->box.MoveThis(associated.box.GetCenter());
	Vec2& unitX = *new Vec2("unitX");
	//Vec2& direction = target - associated.box.GetCenter();
	float angle = (target - associated.box.GetCenter()).GetAngle(unitX);
	Component* bullet = new Bullet(*bulletGO, angle, BULLET_DMG, BULLET_MAX_DISTANCE, "img/minionbullet1.png");
	bulletGO->AddComponent(bullet);
	Game::GetInstance().GetState().AddObject(bulletGO);
}
