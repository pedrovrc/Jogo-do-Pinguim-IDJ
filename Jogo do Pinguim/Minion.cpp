#include "Minion.h"
#include "Sprite.h"

#define ANG_VELOC M_PI/60;

Minion::Minion(GameObject& associated,
		weak_ptr<GameObject> alienCenterArg,
		float arcOffsetDeg) : Component(associated) {
	Component* img = new Sprite(associated, "img/minion.png");
	associated.AddComponent(img);
	alienCenter = alienCenterArg.lock().get();
	arc = arcOffsetDeg * M_PI/180;

	//calcular primeiro valor da box
	Vec2 offset;
	offset.Set(200,0);
	offset = offset.Rotate(arc);
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
	offset = offset.Rotate(arc);
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

}
