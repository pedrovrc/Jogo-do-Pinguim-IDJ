#ifndef FACE_H
#define FACE_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

/*
 * Face é um "inimigo" com uma determinada quantidade de HP.
 */

class Face : public Component{
	int hitpoints;
public:
	Face(GameObject& associated);
	void Damage(int damage);
	void Update(float dt);
	void Render();
	bool Is(string type);
	int GetHP();
};

#endif
