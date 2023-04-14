#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <string>
using namespace std;

#include "GameObject.h"

class Component {
protected:
	GameObject& associated;
public:
	Component(GameObject& associated);
	virtual ~Component();
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool Is(string type) = 0;
};

#endif
