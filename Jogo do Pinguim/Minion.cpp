#include "Minion.h"
#include "Sprite.h"

#define ANG_VELOC M_PI/60;

Minion::Minion(GameObject& associated,
		weak_ptr<GameObject> alienCenterArg,
		float arcOffsetDeg) : Component(associated) {
	cout << "Construtor de Minion" << endl;

	Component* img = new Sprite(associated, "img/minion.png");
	cout << "1" << endl;
	associated.AddComponent(img);
	cout << "2" << endl;
	alienCenter = alienCenterArg.lock().get();
	cout << "3" << endl;
	arc = arcOffsetDeg * M_PI/180;
	cout << "4" << endl;

	//calcular primeiro valor da box
	Vec2 offset;
	cout << "5" << endl;
	offset.Set(200,0);
	cout << "6" << endl;
	offset = offset.Rotate(arc);
	cout << "7" << endl;
	offset += alienCenter->box.GetCenter();
	cout << "8" << endl;
	offset -= *new Vec2(associated.box.w/2, associated.box.h/2);
	cout << "9" << endl;

	// potencial problema
	associated.box.SetPosition(offset);

	cout << "Construiu" << endl;
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
	if (arc > M_PI) arc -= M_PI;
}

void Minion::Render() {

}

bool Minion::Is(string type) {
	if(type == "Minion") return true;
	return false;
}

void Minion::Shoot(Vec2 target) {

}
