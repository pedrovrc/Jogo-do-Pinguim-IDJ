#ifndef BULLET_H
#define BULLET_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

/*
 * Class Bullet
 *
 * Classe que representa o projétil atirado pelo alien.
 */
class Bullet : public Component {
	Vec2 speed;
	float distanceLeft;
	int damage;
public:
	Bullet( GameObject& associated,
			float angle,
			int damage,
			float maxDistance,
			string sprite,
			int frameCount,
			int frameTime );
	void Update(float dt);
	void Render();
	bool Is(string type);
	int GetDamage();
	void Start();
};

#endif
