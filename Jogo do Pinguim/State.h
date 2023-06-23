#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Sound.h"
#include "Music.h"
#include "GameObject.h"
#include "InputManager.h"

/*
 * Classe State
 *
 * Responsável por gerenciar as telas de jogo e os GameObjects.
 */
class State {
	Music music;
	vector<shared_ptr<GameObject>> objectArray;
	bool started;
	bool quitRequested;
	void DeleteObject(GameObject* go);
public:
	State();
	~State();
	void LoadAssets();
	void Update(float dt);
	void Render();
	weak_ptr<GameObject> AddObject(GameObject* go);
	weak_ptr<GameObject> GetObjectPtr(GameObject* go);
	void Start();
	bool QuitRequested();
	static GameObject* GetPlayerGO();
};

#endif
