#include "Vec2.h"

#define _USE_MATH_DEFINES
#include <math.h>

/*
 * Vec2::Vec2()
 *
 * Inicializa objeto com valores zero.
 */
Vec2::Vec2() {
	x = 0;
	y = 0;
}

/*
 * Vec2::Vec2(float x, float y)
 *
 * Inicializa objeto com valores fornecidos.
 */
Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

/*
 * float Vec2::GetMagnitude()
 *
 * Retorna magnitude do vetor representado pelo objeto.
 */
float Vec2::GetMagnitude() {
	return (sqrt(pow(x,2))+(pow(y,2)));
}

/*
 * Vec2& Vec2::GetNormalizedVector()
 *
 * Retorna novo objeto Vec2 cujo vetor aponta na mesma direção, porém tem magnitude 1.
 */
Vec2& Vec2::GetNormalizedVector() {
	float magnit = GetMagnitude();
	if (magnit == 0) {
		return *new Vec2(0, 0);
	}
	return *new Vec2(x/magnit, y/magnit);
}

/*
 * Vec2& Vec2::Vec2Add(Vec2 vector)
 *
 * Método privado que implementa a soma de vetores.
 * Para uso em outro escopo, utilizar operador public "+".
 */
Vec2& Vec2::Vec2Add(Vec2 vector) {
	return *new Vec2(x + vector.x, y + vector.y);
}

/*
 * Vec2& Vec2::Vec2MultiplyScalar(float scalar)
 *
 * Método privado que implementa a multiplicação por escalar.
 * Para uso em outro escopo, utilizar operador public "*".
 */
Vec2& Vec2::Vec2MultiplyScalar(float scalar) {
	return *new Vec2(x * scalar, y * scalar);
}

/*
 * float Vec2::GetDistance(Vec2 point)
 *
 * Retorna distância entre o ponto representado por este objeto e outro ponto fornecido.
 */
float Vec2::GetDistance(Vec2 point) {
	Vec2 negative = this->Vec2MultiplyScalar(-1);
	point.Vec2Add(negative);
	return point.GetMagnitude();
}

/*
 * Vec2& Vec2::Rotate(float angle)
 *
 * Retorna novo objeto Vec2 igual a este rotacionado em um ângulo fornecido.
 */
Vec2& Vec2::Rotate(float angle) {
	float x = (this->x * cos(angle)) - (this->y * sin(angle));
	float y = (this->y * cos(angle)) + (this->x * sin(angle));
	return *new Vec2(x, y);
}

/*
 * Operadores de operações básicas
 */
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

Vec2& Vec2::operator+=(Vec2 b) {
	x += b.x;
	y += b.y;
	return *this;
}

Vec2& Vec2::operator-=(Vec2 b) {
	x -= b.x;
	y -= b.y;
	return *this;
}

Vec2& Vec2::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

Vec2& Vec2::operator/=(float scalar) {
	if (scalar != 0) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
	return *new Vec2(0,0);
}
