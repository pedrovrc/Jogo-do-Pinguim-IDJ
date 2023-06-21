#include "Collider.h"
#include "GeneralFunctions.h"

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
	box.RotateThis(Deg2Rad(associated.angleDeg));
}

void Collider::Render() {

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
