#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "GeneralFunctions.h"
#include "Collider.h"
#include "Bullet.h"

Alien::Action::Action(ActionType type, float x, float y) {
	pos.x = x;
	pos.y = y;
	this->type = type;
}

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
	speed = *new Vec2(0,0);
	hp = MAX_HP;

	Component* img = new Sprite(associated, "img/alien.png", 1, 0);
	associated.AddComponent(img);

	Component* collider = new Collider(associated);
	associated.AddComponent(collider);
}

Alien::~Alien() {

}

/*
 * void Alien::Start()
 *
 * Popula o vetor de minions.
 */
void Alien::Start() {
	State& state = Game::GetInstance().GetState();

	// cria minions
	for(int i = 0; i < MINION_COUNT; i++) {
		GameObject* minionGO = new GameObject;
		Component* minion = new Minion( *minionGO,
										state.GetObjectPtr(&associated),
										(i*(360/MINION_COUNT)),
										RandomFloat(MIN_SIZE, MAX_SIZE) );
		minionGO->AddComponent(minion);
		minionArray.emplace_back(state.AddObject(minionGO));
	}
}

/*
 * void Alien::Update(float dt)
 *
 * - Checa se alien ainda está vivo;
 * - Enfileira ações novas na taskQueue;
 * - Executa ações enfileiradas:
 * 	   - Uma ação executada por frame;
 * 	   - Prioriza ações de movimento;
 * - Rotaciona sprite do alien.
 */
void Alien::Update(float dt) {
	// checar se esta vivo
		if (hp <= 0) {
			associated.RequestDelete();
			int i = 0;
			while (i < (int)minionArray.size()) {
				minionArray[i].lock().get()->RequestDelete();
				i++;
			}
			PlayDeathAnimation();
			return;
		}

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

	// rotacionar sprite
	associated.angleDeg -= ROTATION_SPEED;
	if (associated.angleDeg < 0) associated.angleDeg -= 360;
}

void Alien::Render() {

}

bool Alien::Is(string type) {
	if (type == "Alien") return true;
	return false;
}

void Alien::NotifyCollision(GameObject& other) {
	Component* cpt;

	// Colisao com Bullet
	cpt = other.GetComponent("Bullet");
	if (cpt != nullptr) {
		Bullet* bull = (Bullet*) cpt;
		if (bull->targetsPlayer == false) hp -= bull->GetDamage();
		cout << "Alien HP = " << hp << endl;
	}
}

/*
 *	Minion* Alien::GetClosestMinion(Vec2 target)
 *
 *	Retorna ponteiro para o minion mais próximo ao ponto fornecido.
 */
Minion* Alien::GetClosestMinion(Vec2 target) {
	float smallest_dist;
	int closest;
	GameObject* minionGO;
	for (int i = 0; i < MINION_COUNT; i++) {
		minionGO = minionArray[i].lock().get();
		if (i == 0 || minionGO->box.GetCenter().GetDistance(target) < smallest_dist) {
			closest = i;
			smallest_dist = minionGO->box.GetCenter().GetDistance(target);
		}
	}
	minionGO = minionArray[closest].lock().get();
	return (Minion*)minionGO->GetComponent("Minion");
}

void Alien::PlayDeathAnimation() {
	State* state = &Game::GetInstance().GetState();
	GameObject* explosionGO = new GameObject();

	Sprite* explosion = new Sprite(*explosionGO, "img/aliendeath.png", 4, 250, 1);
	explosionGO->AddComponent((Component*)explosion);

	explosionGO->box.SetCenterPosition(associated.box.GetCenter());

	Sound* boom = new Sound(*explosionGO, "audio/boom.wav");
	boom->Play(1);
	explosionGO->AddComponent((Component*)boom);

	state->AddObject(explosionGO);
}
