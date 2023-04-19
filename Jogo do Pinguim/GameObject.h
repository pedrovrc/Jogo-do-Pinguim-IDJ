#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <bits/stdc++.h>
using namespace std;

#include "Rect.h"
#include "Component.h"

class GameObject {
	vector<Component*> components{};
	bool isDead;
public:
	GameObject();
	~GameObject();
	void Update(float dt);
	void Render();
	bool IsDead();
	void RequestDelete();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	Component* GetComponent(string type);
	Rect box;
};

#endif
