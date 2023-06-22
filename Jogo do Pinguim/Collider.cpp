#include "Collider.h"
#include "GeneralFunctions.h"
#include "Camera.h"

Collider::Collider( GameObject& associated,
			  	  	Vec2 scale,
					Vec2 offset ) : Component(associated) {
	this->scale = scale;
	this->offset = offset;
	//box?
}

void Collider::Update(float dt) {
	box = associated.box.GetScaledCopy(scale);
	box.MoveThis(offset);
	//box.RotateThis(Deg2Rad(associated.angleDeg));
}

void Collider::Render() {
	if (1) {
		Vec2 center( box.GetCenter() );
		SDL_Point points[5];

		Vec2 point;
		point = (Vec2(box.x, box.y) - center).GetRotated( associated.angleDeg/(180/M_PI) ) + center - Camera::pos;
		points[0] = {(int)point.x, (int)point.y};
		points[4] = {(int)point.x, (int)point.y};

		point = (Vec2(box.x + box.w, box.y) - center).GetRotated( associated.angleDeg/(180/M_PI) ) + center - Camera::pos;
		points[1] = {(int)point.x, (int)point.y};

		point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated( associated.angleDeg/(180/M_PI) ) + center - Camera::pos;
		points[2] = {(int)point.x, (int)point.y};

		point = (Vec2(box.x, box.y + box.h) - center).GetRotated( associated.angleDeg/(180/M_PI) ) + center - Camera::pos;
		points[3] = {(int)point.x, (int)point.y};

		SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
	}
}

void Collider::Start() {

}

bool Collider::Is(string type) {
	if (type == "Collider")
		return true;
	else
		return false;
}

void Collider::SetScale(Vec2 newScale) {
	scale.Set(newScale.x, newScale.y);
}

void Collider::SetOffset(Vec2 newOffset) {
	offset.Set(newOffset.x, newOffset.y);
}

void Collider::NotifyCollision(GameObject& other) {

}
