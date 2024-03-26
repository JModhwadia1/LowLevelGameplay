#pragma once
#include "Object.h"
class GameObject;

class Component : public Object
{
public:
	Component(GameObject* owner) : _GameObject(owner) {}
	virtual ~Component() {}

	GameObject* GetGameObject() { return _GameObject; }

	virtual void OwnerActiveChange(bool newActive) {}

	virtual void Update(float dt) {}

protected:
	GameObject* _GameObject;
};

