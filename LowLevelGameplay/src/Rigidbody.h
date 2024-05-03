#pragma once
#include "Transform.h"

class Rigidbody
{
public:
	Rigidbody(Transform* transform);
	~Rigidbody();

	void Update(float deltaTime);
	
	bool IsKinematic;
	
	void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
	void SetNetForce(LLGP::Vector2f force) { _netForce = force; }
	LLGP::Vector2f GetNetForce() { return _netForce; }
	void AddForce(LLGP::Vector2f force) { mVelocity += force; }

	void ResetVelocity() { mVelocity = LLGP::Vector2f(0, 0); }
	void SetDirection(LLGP::Vector2f direction) { mDirection = direction; }
	LLGP::Vector2f GetAcceleration() { return mAcceleration; }
	LLGP::Vector2f GetVelocity() { return mVelocity; }
	void SetVelocity(LLGP::Vector2f velocity) { mVelocity = velocity; }
	float GetMaxSpeed() { return mMaxSpeed; }
	void ApplyImpluse(LLGP::Vector2f impulse) { mVelocity += impulse; }
	float GetInverseMass() { if (mMass == 0) { return 0; return 1.0f / mMass; } }
protected:
	LLGP::Vector2f mVelocity = LLGP::Vector2f(0.0f, 0.0f);
	LLGP::Vector2f mAcceleration = LLGP::Vector2f(0.0f, 0.0f);
	LLGP::Vector2f mDirection = LLGP::Vector2f(0.0f, 0.0f);


private:
	float mMaxSpeed; 
	Transform* _transform;
	LLGP::Vector2f _netForce;
	float mMass = 1.0f;

};

