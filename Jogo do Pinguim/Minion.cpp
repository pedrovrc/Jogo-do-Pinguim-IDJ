#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"
#include "GeneralFunctions.h"

#define ANG_VELOC M_PI/60
#define BULLET_DMG 10
#define BULLET_MAX_DISTANCE 1000

Minion::Minion( GameObject& associated,
				weak_ptr<GameObject> alienCenterArg,
				float arcOffsetDeg,
				float size ) : Component(associated) {
	Component* img = new Sprite(associated, "img/minion.png", 1, 0);
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
	associated.box.SetPosition(offset);

	// aplicar tamanho
	Sprite* spriteimg = (Sprite*)img;
	spriteimg->SetScale(size, size);
}

void Minion::Start() {

}

/*
 * 	void Minion::Update(float dt)
 *
 *	- Checa por existência do alien para requisitar deleção;
 *	- Orbita em volta de alien;
 *	- Rotaciona o sprite para ficar alinhado com alien.
 */
void Minion::Update(float dt) {
	if (alienCenter == nullptr) {
		associated.RequestDelete();
		return;
	}
	// orbitar em volta de alien
	Vec2 center = alienCenter->box.GetCenter();
	Vec2 offset;
	offset.Set(200,0);
	offset.RotateThis(arc);
	offset += center;
	offset -= *new Vec2(associated.box.w/2, associated.box.h/2);
	associated.box.SetPosition(offset);
	arc += ANG_VELOC;
	if (arc >= 2.0f * M_PI) arc = 0;

	// rotacionar
	Vec2 direction = center - associated.box.GetCenter();
	associated.angleDeg = Rad2Deg(direction.GetAngle());
}

void Minion::Render() {

}

bool Minion::Is(string type) {
	if(type == "Minion") return true;
	return false;
}

/*
 *	void Minion::Shoot(Vec2 target)
 *
 *	Cria instância de Bullet e adiciona à lista de objetos de State.
 */
void Minion::Shoot(Vec2 target) {
	GameObject* bulletGO = new GameObject();
	bulletGO->box.MoveThis(associated.box.GetCenter());
	Vec2& unitX = *new Vec2("unitX");
	float angle = (target - associated.box.GetCenter()).GetAngle(unitX);
	Component* bullet = new Bullet( *bulletGO,
									angle,
									BULLET_DMG,
									BULLET_MAX_DISTANCE,
									"img/minionbullet2.png",
									3,
									100 );
	bulletGO->AddComponent(bullet);
	Game::GetInstance().GetState().AddObject(bulletGO);
}
