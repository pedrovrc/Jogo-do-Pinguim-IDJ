#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <bits/stdc++.h>
using namespace std;

class InputManager {
	bool mouseState[6];
	int mouseUpdate[6];
	unordered_map<int,bool> keyState;
	unordered_map<int, int> keyUpdate;
	bool quitRequested;
	int updateCounter;
	int mouseX;
	int mouseY;
	InputManager();
	~InputManager();
public:
	void Update();
	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);
	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);
	int GetMouseX();
	int GetMouseY();
	bool QuitRequested();
	static InputManager& GetInstance();
};

#endif
