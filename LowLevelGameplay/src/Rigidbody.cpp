#include "Rigidbody.h"
#include <SFML/Window/Mouse.hpp>
Rigidbody::Rigidbody(Transform* transform)
{
	_transform = transform;
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update(float deltaTime)
{
	
	// Get pos each frame
	LLGP::Vector2f pos = _transform->GetPosition();
	// Get Accel
    mAcceleration += _netForce / 1.0f;

	// Get velocity
	mVelocity += mAcceleration * deltaTime;

	// Increase pos
	pos += mVelocity * deltaTime;
	
	// Set position
	_transform->SetPosition(pos);

	// set it to 0 as its calculated each frame
	mAcceleration = LLGP::Vector2f::zero;
	_netForce = LLGP::Vector2f::zero;
}

