#ifndef STAGESTATE_H
#define STAGESTATE_H

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
class StageState {
	Music music;
	vector<shared_ptr<GameObject>> objectArray;
	bool started;
	bool quitRequested;
	void DeleteObject(GameObject* go);
public:
	StageState();
	~StageState();
	void LoadAssets();
	void Update(float dt);
	void Render();
	weak_ptr<GameObject> AddObject(GameObject* go);
	weak_ptr<GameObject> GetObjectPtr(GameObject* go);
	void Start();
	bool QuitRequested();
	weak_ptr<GameObject> GetPlayerGO();
};

#endif
