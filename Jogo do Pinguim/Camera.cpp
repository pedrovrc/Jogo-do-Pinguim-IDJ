#include "Camera.h"
GameObject* Camera::focus;
Vec2 Camera::velocity;
Vec2 Camera::pos;

#define CAMERA_SPEED 10

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = nullptr;
}

/*
 * void Camera::Update(float dt)
 *
 * Atualiza posição da câmera com abse no input e no tempo decorrido.
 */
void Camera::Update(float dt) {
	// se camera tiver foco, centralize-o na tela
	if (focus != nullptr) {
		pos.Set(focus->box.x, focus->box.y);
		return;
	}

	// se nao tiver foco, responde a input
	// seta velocidade com base em dt e teclas pressionadas
	// soma-se a posicao
	InputManager& input = InputManager::GetInstance();
	velocity.x = 0;
	velocity.y = 0;
	if (input.KeyPress(LEFT_ARROW_KEY) || input.IsKeyDown(LEFT_ARROW_KEY)) {
		velocity.x -= CAMERA_SPEED;
	}
	if (input.KeyPress(RIGHT_ARROW_KEY) || input.IsKeyDown(RIGHT_ARROW_KEY)) {
		velocity.x += CAMERA_SPEED;
	}
	if (input.KeyPress(UP_ARROW_KEY) || input.IsKeyDown(UP_ARROW_KEY)) {
		velocity.y -= CAMERA_SPEED;
	}
	if (input.KeyPress(DOWN_ARROW_KEY) || input.IsKeyDown(DOWN_ARROW_KEY)) {
		velocity.y += CAMERA_SPEED;
	}
	pos += velocity;
}
