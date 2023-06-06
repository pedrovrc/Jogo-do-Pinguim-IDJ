#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Minion.h"

#define MAX_HP 30
#define MAX_SPEED 30

Alien::Action::Action(ActionType type, float x, float y) {
	pos.x = x;
	pos.y = y;
	this->type = type;
}

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
	speed = *new Vec2(0,0);
	hp = MAX_HP;

	// teste, remover depois
	flag = true;

	Component* img = new Sprite(associated, "img/alien.png");
	associated.AddComponent(img);
}

Alien::~Alien() {

}

void Alien::Start() {
	State& state = Game::GetInstance().GetState();

	// cria minions
	for(int i = 0; i < 3; i++) {
		GameObject* minionGO = new GameObject;
		Component* minion = new Minion(*minionGO, state.GetObjectPtr(&associated), (i*120.0f));
		minionGO->AddComponent(minion);
		minionArray.emplace_back(state.AddObject(minionGO));
	}
}

void Alien::Update(float dt) {
	InputManager* input = &InputManager::GetInstance();

	// coloca acoes na fila
	if(input->MousePress(LEFT_MOUSE_BUTTON) || input->MousePress(RIGHT_MOUSE_BUTTON)) {
		int mouseX = input->GetMouseX() + Camera::pos.x;
		int mouseY = input->GetMouseY() + Camera::pos.y;
		if (input->MousePress(LEFT_MOUSE_BUTTON)) {
			Action::ActionType type = Action::ActionType::SHOOT;
			taskQueue.emplace(*new Action(type, mouseX, mouseY));
		} else {
			Action::ActionType type = Action::ActionType::MOVE;
			taskQueue.emplace(*new Action(type, mouseX, mouseY));
		}
	}

	// executar acoes pendentes
	// uma acao por frame
	Action* act;
	if (taskQueue.empty() == false) {
		act = &taskQueue.front();
		if (act->type == Action::ActionType::MOVE) {
			if (act->pos.GetDistance(associated.box.GetCenter()) >= MAX_SPEED) {
				Vec2 direction = act->pos - associated.box.GetCenter();
				speed = direction.GetNormalizedVector() * MAX_SPEED;
				associated.box.MoveThis(speed);
			} else {
				Vec2 offset;
				offset.Set(associated.box.w/2, associated.box.h/2);
				associated.box.SetPosition(act->pos - offset);
				taskQueue.pop();
				speed.Set(0,0);
			}
		} else if (act->type == Action::ActionType::SHOOT) {
			GameObject* minionGO = minionArray[1].lock().get();
			Minion* minion = (Minion*)minionGO->GetComponent("Minion");
			minion->Shoot(act->pos);
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
