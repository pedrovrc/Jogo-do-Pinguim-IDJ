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

float Rect::GetCenterDist(Rect box) {
	Vec2 center1 = this->GetCenter();
	Vec2 center2 = box.GetCenter();
	return center1.GetDistance(center2);
}

void Rect::MoveThis(Vec2 vector) {
	this->x += vector.x;
	this->y += vector.y;
}

Rect& Rect::GetTranslatedRect(Vec2 vector) {
	return *new Rect(vector.x, vector.y, this->w, this->h);
}

	// nao considera rotacao
bool Rect::IsInside(Vec2 point) {
	float limit_lo_x = this->x;
	float limit_hi_x = this->x + this->w;
	float limit_lo_y = this->y;
	float limit_hi_y = this->y + this->h;
	if (point.x < limit_hi_x && point.x > limit_lo_x
		&& point.y < limit_hi_y && point.y > limit_lo_y) {
		return true;
	}
	return false;
}
