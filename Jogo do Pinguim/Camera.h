#ifndef CAMERA_H
#define CAMERA_H

#include <bits/stdc++.h>
using namespace std;

#include "GameObject.h"
#include "InputManager.h"

class Camera {
	static GameObject* focus;
public:
	static Vec2 speed;
	static Vec2 pos;
	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);
};

#endif
