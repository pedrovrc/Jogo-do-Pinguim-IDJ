#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

#define PENGUIN_DMG 10
#define PENGUIN_MAX_DISTANCE 1000
#define BULLET_OFFSET 70

class PenguinCannon : public Component {
	weak_ptr<GameObject> pbody;
	float angle;
public:
	PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody);
	void Update(float dt);
	void Render();
	bool Is(string type);
	void Start();
	void Shoot();
};

#endif