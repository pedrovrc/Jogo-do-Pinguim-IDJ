#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

class CameraFollower : public Component {
public:
	CameraFollower(GameObject& go);
	void Update(float dt);
	void Render();
	bool Is(string type);
};

#endif
