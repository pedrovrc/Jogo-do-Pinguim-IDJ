#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "GeneralFunctions.h"

#define MAX_HP 30
#define MAX_SPEED 30
#define MINION_COUNT 3
#define ROTATION_SPEED 0.5

Alien::Action::Action(ActionType type, float x, float y) {
	pos.x = x;
	pos.y = y;
	this->type = type;
}

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
	speed = *new Vec2(0,0);
	hp = MAX_HP;

	Component* img = new Sprite(associated, "img/alien.png");
	associated.AddComponent(img);
}

Alien::~Alien() {

}

void Alien::Start() {
	State& state = Game::GetInstance().GetState();

	// cria minions
	for(int i = 0; i < MINION_COUNT; i++) {
		GameObject* minionGO = new GameObject;
		Component* minion = new Minion( *minionGO,
										state.GetObjectPtr(&associated),
										(i*(360/MINION_COUNT)),
										RandomFloat(1, 1.5) );
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
	// uma acao por frame, prioridade por acoes de movimento
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
			Minion* minion = GetClosestMinion(act->pos);
			minion->Shoot(act->pos);
			taskQueue.pop();
		}
	}

	// checar se esta vivo
	if (hp <= 0) associated.RequestDelete();

	// rotacionar
	associated.angleDeg -= ROTATION_SPEED;
	if (associated.angleDeg < 0) associated.angleDeg -= 360;
}

void Alien::Render() {

}

bool Alien::Is(string type) {
	if (type == "Alien") return true;
	return false;
}

Minion* Alien::GetClosestMinion(Vec2 target) {
	float smallest_dist;
	int closest;
	GameObject* minionGO;
	for (int i = 0; i < MINION_COUNT; i++) {
		minionGO = minionArray[i].lock().get();
		if (i == 0) {
			closest = 0;
			smallest_dist = minionGO->box.GetCenter().GetDistance(target);
			continue;
		} else if (minionGO->box.GetCenter().GetDistance(target) < smallest_dist) {
			closest = i;
			smallest_dist = minionGO->box.GetCenter().GetDistance(target);
		}
	}
	minionGO = minionArray[closest].lock().get();
	return (Minion*)minionGO->GetComponent("Minion");
}
