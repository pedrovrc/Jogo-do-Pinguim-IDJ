#include "Bullet.h"
#include "Sprite.h"

#define BULLET_SPEED 50

Bullet::Bullet( GameObject& associated,
				float angle,
				int damage,
				float maxDistance,
				string sprite ) : Component(associated) {
	Component* img = new Sprite(associated, sprite);
	associated.AddComponent(img);
	Sprite* spritecpt = (Sprite*)img;
	associated.box.MoveThis(*new Vec2(-spritecpt->GetWidth()/2, -spritecpt->GetHeight()/2));

	this->damage = damage;
	distanceLeft = maxDistance;
	speed.Set(BULLET_SPEED, 0);
	speed.RotateThis(angle);
}

void Bullet::Update(float dt) {
	Vec2 velocity = speed * (dt * 10);
	associated.box.MoveThis(velocity);
	distanceLeft -= velocity.GetMagnitude();
	if (distanceLeft <= 0) {
		associated.RequestDelete();
	}
	return;
}

void Bullet::Render() {

}

bool Bullet::Is(string type) {
	if (type == "Bullet") return true;
	return false;
}

int Bullet::GetDamage() {
	return damage;
}

void Bullet::Start() {

}
