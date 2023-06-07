#ifndef ALIEN_H
#define ALIEN_H

#include <bits/stdc++.h>
using namespace std;

#include "Vec2.h"
#include "GameObject.h"
#include "Minion.h"

class Alien : public Component {
	class Action {
	public:
		enum ActionType {MOVE, SHOOT};

		ActionType type;
		Vec2 pos;

		Action(ActionType type, float x, float y);
	};

	Vec2 speed;
	int hp;

	queue<Action> taskQueue;
	vector<weak_ptr<GameObject>> minionArray;
public:
	Alien(GameObject& associated, int nMinions);
	~Alien();

	// teste, remover depois
	Vec2 a, b;

	void Start();
	void Update(float dt);
	void Render();
	bool Is(string type);
	Minion* GetClosestMinion(Vec2 target);
};

#endif
