#pragma once
#include "Transform.h"

class Rigidbody
{
public:
	Rigidbody(Transform* transform);
	~Rigidbody();

	void Update(float deltaTime);
	
	void SetDirection(LLGP::Vector2f direction) { mDirection = direction; }
	void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
	LLGP::Vector2f mAcceleration = LLGP::Vector2f(0.0f, 0.0f);
	LLGP::Vector2f mVelocity = LLGP::Vector2f(0.0f, 0.0f);
	LLGP::Vector2f mDirection = LLGP::Vector2f(0.0f, 0.0f);
	void SetNetForce(LLGP::Vector2f force) { _netForce = force; }
	LLGP::Vector2f GetNetForce() { return _netForce; }
	void AddForce(LLGP::Vector2f force) { _netForce += force; }
private:
	float mMaxSpeed; 
	Transform* _transform;
	LLGP::Vector2f _netForce;

};

