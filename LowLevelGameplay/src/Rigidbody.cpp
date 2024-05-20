#include "Rigidbody.h"
#include <SFML/Window/Mouse.hpp>
Rigidbody::Rigidbody(Transform* transform, sf::Sprite* sprite)
{
	_transform = transform;
	_sprite = sprite;
}

Rigidbody::~Rigidbody()
{
	_transform = nullptr;
	_sprite = nullptr;
}

void Rigidbody::Update(float deltaTime)
{
	
	// Get pos each frame
	LLGP::Vector2f pos = _transform->GetPosition();

	// Increase pos
	pos += (mVelocity / mMass) * deltaTime;
	
	// Set position
	_transform->SetPosition(pos);
	_sprite->setPosition(_transform->GetPosition());

	//// set it to 0 as its calculated each frame
	mAcceleration = LLGP::Vector2f::zero;
	mVelocity = LLGP::Vector2f::zero;
	
}

