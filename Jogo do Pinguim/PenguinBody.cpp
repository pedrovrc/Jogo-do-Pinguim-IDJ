#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "Sprite.h"
#include "InputManager.h"

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody (GameObject& associated) : Component(associated) {
	player = this;
	speed.Set(0, 0);
	linearSpeed = 0;
	angle = 0;
	hp = HP_MAX;
	Sprite* sprbody = new Sprite(associated, "img/penguin.png");
	associated.AddComponent((Component*)sprbody);
}

PenguinBody::~PenguinBody () {
	player = nullptr;
}

void PenguinBody::Start() {
	State* state = &Game::GetInstance().GetState();
	GameObject* cannonGO = new GameObject();
	PenguinCannon* cannon = new PenguinCannon(*cannonGO, state->GetObjectPtr(&associated));
	cannonGO->AddComponent((Component*)cannon);
	pcannon = state->AddObject(cannonGO);
}

void PenguinBody::Update(float dt) {
	if (hp <= 0) {
		associated.RequestDelete();
		return;
	}

	InputManager* input = &InputManager::GetInstance();

	// teclas W ou S -> acelera ou desacelera
	if ((input->KeyPress(W_KEY) || input->IsKeyDown(W_KEY)) && linearSpeed <= VEL_MAX)
		linearSpeed += ACCELERATION;
	if ((input->KeyPress(S_KEY) || input->IsKeyDown(S_KEY)) && linearSpeed >= VEL_MIN)
			linearSpeed -= ACCELERATION;

	// teclas A ou D -> muda angulo
	if (input->KeyPress(A_KEY) || input->IsKeyDown(A_KEY))
		angle -= ANGLE_CHANGE;
	if (input->KeyPress(D_KEY) || input->IsKeyDown(D_KEY))
		angle += ANGLE_CHANGE;

	if (linearSpeed > 0) linearSpeed -= FRICTION;
	if (linearSpeed < 0) linearSpeed += FRICTION;

	speed.Set(linearSpeed, 0);
	speed.RotateThis(angle * M_PI/180);
	associated.box.MoveThis(speed);
	associated.angleDeg = angle;

}

void PenguinBody::Render() {

}

bool PenguinBody::Is(string type) {
	if (type == "PenguinBody") return true;
	return false;
}

