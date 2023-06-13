#ifndef PENGUINBODY_H
#define PENGUINBODY_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

#define HP_MAX 100
#define ACCELERATION 0.8
#define VEL_MAX 15
#define VEL_MIN -10
#define ANGLE_CHANGE 5
#define FRICTION 0.2

class PenguinBody : public Component {
	weak_ptr<GameObject> pcannon;
	Vec2 speed;
	float linearSpeed;
	float angle;
	int hp;
public:
	static PenguinBody* player;

	PenguinBody(GameObject& associated);
	~PenguinBody();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(string type);
};

#endif
