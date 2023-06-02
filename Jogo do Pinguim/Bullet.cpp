#include "Bullet.h"

#define BULLET_SPEED 20

Bullet::Bullet(GameObject& associated,
		float angle,
		int damage,
		float maxDistance,
		string sprite) : Component(associated) {
	this->damage = damage;
	// terminar
}
