#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Sound.h"
#include "Music.h"
#include "GameObject.h"

class State {
	Sprite bg;
	Music music;
	vector<unique_ptr<GameObject>> objectArray;

	bool quitRequested;
	void Input();
	void AddObject(int mouseX, int mouseY);
	void DeleteObject(GameObject& go);
public:
	State();
	~State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
};

#endif
