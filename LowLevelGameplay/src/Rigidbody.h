#pragma once
#include "Transform.h"

class Rigidbody
{
public:
	Rigidbody(Transform* transform);
	~Rigidbody();

	void Update(float deltaTime);
	void AddForce(LLGP::Vector2f Force);
	void SetDirection(LLGP::Vector2f direction) { mDirection = direction; }
	void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
private:
	float mMaxSpeed = 300.0f;
	Transform* _transform;
	LLGP::Vector2f mAcceleration = LLGP::Vector2f(0.0f, 0.0f);
	LLGP::Vector2f mVelocity = LLGP::Vector2f(0.0f, 0.0f);
	LLGP::Vector2f mDirection = LLGP::Vector2f(0.0f, 0.0f);

};

