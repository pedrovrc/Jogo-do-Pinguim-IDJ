#include "Camera.h"
GameObject* Camera::focus;
Vec2 Camera::speed;
Vec2 Camera::pos;

#define CAMERA_SPEED 10

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = nullptr;
}

void Camera::Update(float dt) {
	// se camera tiver foco, centralize-o na tela
	if (focus != nullptr) {
		// centralizar
	}

	// se nao tiver foco, responder a input
	// setar velocidade com base em dt e teclas pressionadas
	// soma-se a posicao
	InputManager* input = &(InputManager::GetInstance());
	speed.x = 0;
	speed.y = 0;
	if (input->KeyPress(LEFT_ARROW_KEY)) {
		speed.x -= CAMERA_SPEED;
	}
	if (input->KeyPress(RIGHT_ARROW_KEY)) {
		speed.x += CAMERA_SPEED;
	}
	if (input->KeyPress(UP_ARROW_KEY)) {
		speed.y -= CAMERA_SPEED;
	}
	if (input->KeyPress(DOWN_ARROW_KEY)) {
		speed.y += CAMERA_SPEED;
	}
	pos += speed;
}
