#ifndef VEC2_H
#define VEC2_H

#include <bits/stdc++.h>
using namespace std;

class Vec2 {
	Vec2& Vec2Add(Vec2 vector);
	Vec2& Vec2MultiplyScalar(float scalar);
public:
	float x;
	float y;
	Vec2();
	Vec2(float x, float y);
	float GetMagnitude();
	Vec2& GetNormalizedVector();
	float GetDistance(Vec2 point);

	Vec2& operator+(Vec2& b);
	Vec2& operator-(Vec2& b);
	Vec2& operator*(float scalar);
	Vec2& operator/(float scalar);

	// implementar:
	// - inclinacao de um vetor
	// - inclinacao da reta dada por dois pontos
	// - rotacao em um determinado angulo

};

#endif
