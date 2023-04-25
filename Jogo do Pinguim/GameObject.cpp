#include "GameObject.h"

GameObject::GameObject() {
	isDead = false;
}

GameObject::~GameObject() {
	while (components.empty() == false) {
		components.erase(components.end() - 1);
	}
	components.clear();
}

void GameObject::Update(float dt) {
	int i = 0;
	Component* cpt;
	while (components.begin() + i != components.end()) {
		cpt = components[i];
		cpt->Update(dt);
		i++;
	}
}

void GameObject::Render() {
	int i = 0;
	Component* cpt;
	while (components.begin() + i != components.end()) {
		cpt = components[i];
		cpt->Render();
		i++;
	}
}

bool GameObject::IsDead() {
	return isDead;
}

void GameObject::RequestDelete() {
	isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
	components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
	int size = components.size(), i = 0;
	while (i < size) {
		if (cpt == components[i]) {
			components.erase(components.begin() + i);
			return;
		}
		i++;
	}
}

Component* GameObject::GetComponent(string type) {
	int size = components.size(), i =0;
	Component* cpt;
	while (i < size) {
		cpt = components[components.begin() + i];
		if (cpt->Is(type)) {
			return cpt;
		}
	}
	return nullptr;
}
