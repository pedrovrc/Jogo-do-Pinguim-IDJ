#include "GameObject.h"

GameObject::GameObject() {
	isDead = false;
}

GameObject::~GameObject() {
	int i = 0;
	while (components.empty() == false) {
		components.erase(components.begin());
	}
}

void GameObject::Update(float dt) {
	int i = 0;
	while (components.begin() + i != components.end()) {
		components[i].Update(0);
		i++;
	}
}
