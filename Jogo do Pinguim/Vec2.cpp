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

Vec2& Vec2::Vec2MultiplyScalar(float scalar) {
	return *new Vec2(this->x * scalar, this->y * scalar);
}

float Vec2::GetMagnitude() {
	return (sqrt((this->x^2)+(this->y^2)));
}

Vec2& Vec2::GetNormalizedVector() {
	float magnit = GetMagnitude();
	if (magnit == 0) {
		return *new Vec2(0, 0);
	}
	return *new Vec2(this->x/magnit, this->y/magnit);
}

float Vec2::GetDistance(Vec2 point) {
	Vec2 neg = this->Vec2MultiplyScalar(-1);
	point = point.Vec2Add(neg);
	return point.GetMagnitude();
}

Vec2& Vec2::operator+(Vec2& b) {
	return *this->Vec2Add(b);
}

Vec2& Vec2::operator-(Vec2& b) {
	b = *b.Vec2MultiplyScalar(-1);
	return *this->Vec2Add(b);
}

Vec2& Vec2::operator*(float scalar) {
	return *this->Vec2MultiplyScalar(scalar);
}

Vec2& Vec2::operator/(float scalar) {
	if (scalar != 0) {
		scalar = 1/scalar;
	}
	return *this->Vec2MultiplyScalar(scalar);
}
