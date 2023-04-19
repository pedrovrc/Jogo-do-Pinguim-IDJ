#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"

class State {
	Sprite bg;
	Music music;
	bool quitRequested;
	void Input();
	void AddObject(int mouseX, int mouseY);
	vector<unique_ptr<GameObject>> objectArray;
public:
	State();
	~State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
};

#endif
