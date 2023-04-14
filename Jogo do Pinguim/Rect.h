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
	Rect& Translate(Vec2 vector);

};
#endif
