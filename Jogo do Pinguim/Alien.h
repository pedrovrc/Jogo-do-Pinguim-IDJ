#ifndef ALIEN_H
#define ALIEN_H

#include <bits/stdc++.h>
using namespace std;

#include "Vec2.h"
#include "GameObject.h"
#include "Minion.h"
#include "Timer.h"

#define MAX_HP 30
#define MAX_SPEED 4
#define MINION_COUNT 6
#define ROTATION_SPEED 0.5
#define MIN_SIZE 1
#define MAX_SIZE 1.5
#define ALIEN_DMG 10
#define REST_COOLDOWN 0.2

/*
 * Class Alien
 *
 * Classe que representa a entidade central do oponente.
 */
class Alien : public Component {
	enum AlienState { MOVING, RESTING };
	AlienState state;
	int hp;
	Vec2 speed;
	Vec2 destination;
	Timer restTimer;

	vector<weak_ptr<GameObject>> minionArray;
public:
	static int alienCount;

	Alien(GameObject& associated, int nMinions, int currentCount);
	~Alien();

	void Start();
	void Update(float dt);
	void Render();
	bool Is(string type);
	void NotifyCollision(GameObject& other);
	Minion* GetClosestMinion(Vec2 target);
	void PlayDeathAnimation();
	void SetCount(int quantity);
};

#endif
