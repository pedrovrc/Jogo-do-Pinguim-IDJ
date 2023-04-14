#ifndef RECT_H
#define RECT_H

#include <iostream>
#include <string>
using namespace std;

#include "Vec2.h"

class Rect {

public:
	float x;
	float y;
	float w;
	float h;
	Rect();
	Rect(float x, float y, float w, float h);
	Vec2& GetCenter();
	float GetCenterDist(Rect box);
	void MoveThis(Vec2 vector);
	Rect& GetTranslatedRect(Vec2 vector);
	bool IsInside(Vec2 point);	// nao considera rotacao

	// implementar:
	// - rotacao em um determinado angulo
};
#endif
