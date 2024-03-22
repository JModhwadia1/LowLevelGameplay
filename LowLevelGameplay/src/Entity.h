#pragma once
#include "Transform.h"
#include "Texture2D.h"
#include "Rigidbody.h"

class Entity
{
public:
	Entity(sf::Texture& texture);
	~Entity();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	Rigidbody* GetRigidbody() { return _rigidbody; }
	Texture2D* GetTexture2D() { return _texture; }

private:

	Texture2D* _texture;
	Transform* _transform;
	Rigidbody* _rigidbody;
};


