#ifndef BULLET_H
#define BULLET_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

class Bullet : public Component {
	Vec2 speed;
	float distanceLeft;
	int damage;
public:
	Bullet(GameObject& associated,
			float angle,
			int damage,
			float maxDistance,
			string sprite);
	void Update(float dt);
	void Render();
	bool Is(string type);
	int GetDamage();
}

#endif
