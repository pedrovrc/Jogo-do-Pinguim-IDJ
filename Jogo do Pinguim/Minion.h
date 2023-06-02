#ifndef MINION_H
#define MINION_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

class Minion : public Component {
	GameObject* alienCenter;
	float arc;
public:
	Minion(GameObject& associated,
			weak_ptr<GameObject> alienCenter,
			float arcOffsetDeg = 0);
	void Update(float dt);
	void Render();
	void Start();
	bool Is(string type);
	void Shoot(Vec2 target);
};

#endif