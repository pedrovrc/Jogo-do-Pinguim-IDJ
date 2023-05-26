#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"

#define MAX_HP 30
#define MAX_SPEED 1

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
	speed = *new Vec2(0,0);
	hp = MAX_HP;
	Component* img = new Sprite(associated, "img/alien.png");
	associated.AddComponent(img);
}

Alien::~Alien() {

}

void Alien::Start() {

}

void Alien::Update(float dt) {
	InputManager* input = &InputManager::GetInstance();

	// coloca acoes na fila
	if(input->MousePress(SDL_BUTTON_LEFT) || input->MousePress(SDL_BUTTON_RIGHT)) {
		int mouseX = input->GetMouseX() - Camera::pos.x;
		int mouseY = input->GetMouseY() - Camera::pos.y;
		if (input->MousePress(SDL_BUTTON_LEFT)) {
			Action::ActionType type = "SHOOT";
			taskQueue.emplace(*new Action(type, mouseX, mouseY));
		} else {
			Action::ActionType type = "MOVE";
			taskQueue.emplace(*new Action(type, mouseX, mouseY));
		}
	}

	// executar acoes pendentes
	// uma acao por frame
	Action* act;
	if (taskQueue.empty() == false) {
		act = &taskQueue.front();
		if (act->type == MOVE) {
			if (act->pos.GetDistance(associated.box.GetCenter()) > MAX_SPEED) {
				Vec2 direction = (act->pos - associated.box.GetCenter()).GetNormalizedVector();
				speed = direction;
			} else {
				associated.box.MoveThis(act->pos);
				taskQueue.pop();
			}
		} else if (act->type == SHOOT) {
			taskQueue.pop();
		}
	}

	// checar se esta vivo
	if (hp <= 0) associated.RequestDelete();
}

void Alien::Render() {

}

bool Alien::Is(string type) {
	if (type == "Alien") return true;
	return false;
}
