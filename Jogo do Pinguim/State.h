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
	vector<unique_ptr<GameObject>> objectArray;

	bool quitRequested;
	void AddObject(GameObject* go);
	void AddObjectKeyPress(int mouseX, int mouseY);
	void DeleteObject(GameObject* go);
public:
	State();
	~State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
};

#endif
