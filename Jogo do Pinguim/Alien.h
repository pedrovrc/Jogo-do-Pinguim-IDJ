#ifndef ALIEN_H
#define ALIEN_H

#include <bits/stdc++.h>
using namespace std;

#include "Vec2.h"
#include "GameObject.h"
#include "Minion.h"

#define MAX_HP 30
#define MAX_SPEED 30
#define MINION_COUNT 6
#define ROTATION_SPEED 0.5
#define MIN_SIZE 1
#define MAX_SIZE 1.5

/*
 * Class Alien
 *
 * Classe que representa a entidade central do oponente.
 */
class Alien : public Component {
	/*
	 * Class Action
	 *
	 * Classe interna de Alien que ordena os tipos de ação que ele pode executar.
	 */
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

	void Start();
	void Update(float dt);
	void Render();
	bool Is(string type);
	Minion* GetClosestMinion(Vec2 target);
};

#endif
