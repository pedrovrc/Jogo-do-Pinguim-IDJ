#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <string>
using namespace std;

class Vec2 {

public:
	float x;
	float y;
	Vec2();
	Vec2(float x, float y);
	Vec2& Vec2Add(Vec2 vector);
	Vec2& ScalarProd(float scalar);
	float GetMagnitude();
	Vec2& GetNormalVector();
	//float GetAngle();
	float GetDistance(Vec2 point);

};

#endif
