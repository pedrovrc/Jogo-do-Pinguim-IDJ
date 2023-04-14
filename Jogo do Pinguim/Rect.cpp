#include "Rect.h"

Rect::Rect() {
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
}

Rect::Rect(float x, float y, float w, float h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

	// Retorna objeto Vec2 com coordenadas de centro
Vec2& Rect::GetCenter() {
	return *new Vec2(this->x + (this->w)/2, this->y + (this->y)/2);
}
