#include "Vec2.h"

#define _USE_MATH_DEFINES
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
	return *new Vec2(x + vector.x, y + vector.y);
}

Vec2& Vec2::Vec2MultiplyScalar(float scalar) {
	return *new Vec2(x * scalar, y * scalar);
}

float Vec2::GetMagnitude() {
	return (sqrt(pow(x,2))+(pow(y,2)));
}

Vec2& Vec2::GetNormalizedVector() {
	float magnit = GetMagnitude();
	if (magnit == 0) {
		return *new Vec2(0, 0);
	}
	return *new Vec2(x/magnit, y/magnit);
}

float Vec2::GetDistance(Vec2 point) {
	Vec2 neg = Vec2MultiplyScalar(-1);
	point = point.Vec2Add(neg);
	return point.GetMagnitude();
}

Vec2& Vec2::operator+(Vec2 b) {
	return Vec2Add(b);
}

Vec2& Vec2::operator-(Vec2 b) {
	b = b.Vec2MultiplyScalar(-1);
	return Vec2Add(b);
}

Vec2& Vec2::operator*(float scalar) {
	return Vec2MultiplyScalar(scalar);
}

Vec2& Vec2::operator/(float scalar) {
	if (scalar != 0) {
		scalar = 1/scalar;
	}
	return Vec2MultiplyScalar(scalar);
}

Vec2& Vec2::Rotate(float angle) {
	Vec2& rotated = *new Vec2;
	rotated.x = (x * cos(angle)) - (y * sin(angle));
	rotated.y = (y * cos(angle)) + (x * sin(angle));
	return rotated;
}
