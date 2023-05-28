#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"

#define MAX_HP 30
#define MAX_SPEED 3

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

}

void Alien::Update(float dt) {
	InputManager* input = &InputManager::GetInstance();

	//teste
//	if(input->MousePress(LEFT_MOUSE_BUTTON) || input->MousePress(RIGHT_MOUSE_BUTTON)) {
//		int mouseX = input->GetMouseX() - Camera::pos.x;
//		int mouseY = input->GetMouseY() - Camera::pos.y;
//		if (input->MousePress(LEFT_MOUSE_BUTTON)) {
//			if (flag) {
//				a.Set(mouseX, mouseY);
//			} else {
//				b.Set(mouseX, mouseY);
//			}
//			cout << "MouseX = " << mouseX << ", MouseY = " << mouseY << endl;
//			cout << "Vec2 a: (" << a.x << "," << a.y << ")" << endl;
//			cout << "Vec2 b: (" << b.x << "," << b.y << ")" << endl;
//			double distance = a.GetDistance(b);
//			cout << "Distancia = " << distance << endl;
//			cout << "--------------------------------------" << endl << endl;
//			flag = !flag;
//		}
//	}

	// coloca acoes na fila
	if(input->MousePress(LEFT_MOUSE_BUTTON) || input->MousePress(RIGHT_MOUSE_BUTTON)) {
		int mouseX = input->GetMouseX() - Camera::pos.x;
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
			cout << "act->pos = (" << act->pos.x << "," << act->pos.y << ")" << endl;
			cout << "box = (" << associated.box.x << "," << associated.box.y << ")" << endl;
			cout << "Distance = " << act->pos.GetDistance(associated.box.GetCenter()) << endl;
			cout << "-------------------------" << endl;
			if (act->pos.GetDistance(associated.box.GetCenter()) >= MAX_SPEED) {
				Vec2 direction = act->pos - associated.box.GetCenter();
				speed = direction.GetNormalizedVector() * MAX_SPEED;
				associated.box.MoveThis(speed);
			} else {
				cout << "DONE! ------------------------" << endl;
				cout << "act->pos: ("<< act->pos.x << "," << act->pos.y << ")" << endl;
				cout << "box before: ("<< associated.box.x << "," << associated.box.y << ")" << endl;
				Vec2 offset;
				offset.Set(associated.box.w/2, associated.box.h/2);
				associated.box.SetPosition(act->pos - offset);
				cout << "box after: ("<< associated.box.x << "," << associated.box.y << ")" << endl;
				taskQueue.pop();
				speed.Set(0,0);
			}
		} else if (act->type == Action::ActionType::SHOOT) {
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
