#include "Vec2.h"
#include <math.h>

Vec2::Vec2() {
	this->x = 0;
	this->y = 0;
}

Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vec2& Vec2::Vec2Add(Vec2 vector) {
	return *new Vec2(this->x + vector.x, this->y + vector.y);
}

Vec2& Vec2::Vec2ScalarProd(float scalar) {
	return *new Vec2(this->x * scalar, this->y * scalar);
}

float Vec2::GetMagnitude() {
	return (sqrt((this->x^2)+(this->y^2)));
}

Vec2& Vec2::GetNormalVector() {
	float magnit = GetMagnitude();
	if (magnit == 0) {
		return *new Vec2(0, 0);
	}
	return *new Vec2(this->x/magnit, this->y/magnit);
}

float Vec2::GetDistance(Vec2 point) {
	Vec2 neg = this->ScalarProd(-1);
	point = point.Vec2Add(neg);
	return point.GetMagnitude();
}
