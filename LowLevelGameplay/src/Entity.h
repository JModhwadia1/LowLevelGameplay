#pragma once
#include "Transform.h"
#include "Texture2D.h"
#include "Rigidbody.h"

class Entity
{
public:
	Entity();
	~Entity();
private:

	Texture2D* _texture;
	Transform* _transform;
	Rigidbody* _rigidbody;
};


