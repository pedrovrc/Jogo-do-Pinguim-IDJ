#include "Rect.h"

/*
 * Rect::Rect()
 *
 * Inicializa objeto com dimensões zero e posição (0,0)
 */
Rect::Rect() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

/*
 * Rect::Rect(float x, float y, float w, float h)
 *
 * Inicializa objeto com os parâmetros fornecidos.
 */
Rect::Rect(float x, float y, float w, float h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

/*
 * Vec2& Rect::GetCenter()
 *
 * Retorna objeto Vec2 com coordenadas de centro do retângulo.
 */
Vec2& Rect::GetCenter() {
	return *new Vec2(x + (w/2), y + (h/2));
}

/*
 * float Rect::GetCenterDist(Rect box)
 *
 * Retorna a distância entre o centro deste objeto Rect e outro fornecido.
 */
float Rect::GetCenterDist(Rect box) {
	Vec2 center1 = this->GetCenter();
	Vec2 center2 = box.GetCenter();
	return center1.GetDistance(center2);
}

/*
 * void Rect::MoveThis(Vec2 vector)
 *
 * Modifica os valores x e y para transladar o retângulo de acordo com o vetor fornecido.
 */
void Rect::MoveThis(Vec2 vector) {
	x += vector.x;
	y += vector.y;
}

/*
 * void Rect::SetPosition(Vec2 vector)
 *
 * Modifica os valores x e y para colocar o retângulo no ponto fornecido.
 */
void Rect::SetPosition(Vec2 vector) {
	x = vector.x;
	y = vector.y;
}

/*
 * void Rect::SetDimensions(float w, float h)
 *
 * Modifica os valores w e h para os fornecidos.
 */
void Rect::SetDimensions(float w, float h) {
	this->w = w;
	this->h = h;
}

/*
 * Rect& Rect::GetTranslatedRect(Vec2 vector)
 *
 * Retorna novo objeto Rect de mesmas dimensões mas transladado por vetor fornecido.
 */
Rect& Rect::GetTranslatedCopy(Vec2 vector) {
	return *new Rect(x + vector.x, y + vector.y, this->w, this->h);
}

/*
 * bool Rect::IsInside(Vec2 point)
 *
 * Checa se ponto fornecido está dentro do objeto Rect. Não considera rotações.
 */
bool Rect::IsInside(Vec2 point) {
	float limit_lo_x = x;
	float limit_hi_x = x + w;
	float limit_lo_y = y;
	float limit_hi_y = y + h;
	if (point.x < limit_hi_x && point.x > limit_lo_x
		&& point.y < limit_hi_y && point.y > limit_lo_y) {
		return true;
	}
	return false;
}


