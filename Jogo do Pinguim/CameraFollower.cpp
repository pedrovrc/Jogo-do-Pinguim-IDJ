#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go) {

}

/*
 * void CameraFollower::Update(float dt)
 *
 * Atualiza parâmetros para seguir câmera.
 */
void CameraFollower::Update(float dt) {
	associated.box.MoveThis(*new Vec2(Camera::velocity.x, Camera::velocity.y));
}

void CameraFollower::Start() {

}

void CameraFollower::Render() {

}

bool CameraFollower::Is(string type) {
	if (type == "CameraFollower") return true;
	return false;
}
