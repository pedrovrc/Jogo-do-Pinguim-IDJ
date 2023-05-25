#ifndef RECT_H
#define RECT_H

#include <bits/stdc++.h>
#include <tuple>
using namespace std;

#include "Vec2.h"

/*
 * Classe Rect
 *
 * Implementa um retângulo de dimensões w e h, com seu canto esquerdo superior em (x,y).
 */
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
	Rect& GetTranslatedCopy(Vec2 vector);
	bool IsInside(Vec2 point);	// nao considera rotacao

	// implementar:
	// - rotacao em um determinado angulo
};
#endif
