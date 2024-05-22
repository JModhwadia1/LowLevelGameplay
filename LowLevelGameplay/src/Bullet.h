#pragma once
#include "GameObject.h"

class BoxCollider;
class LineCollider;

struct  BulletLaunchParams
{
	const GameObject* mOwner = nullptr;
	LLGP::Vector2f mStartPos = LLGP::Vector2f(0.0f, 0.0f);
	LLGP::Vector2f mDirection = LLGP::Vector2f(0.0f, 0.0f);

	float mDamage = 10.0f;

};
class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(const Bullet&) = default;
	void Launch(const BulletLaunchParams* params);

	const GameObject* GetOwner() const { return mOwner ? mOwner : this; }
	float GetDamage() const { return mDamage; }
	float GetBulletSpeed() { return mBulletSpeed; }
	void Update(float dt) override;
	void FixedUpdate(float fixedUpdate);
	void OnCollision(GameObject& other) override;

	void Draw(sf::RenderWindow* window)override;
	BoxCollider* mBoxCollider;
	LineCollider* mLineCollider;

private:
	float mBulletSpeed = 500.0f;
	const GameObject* mOwner = nullptr;
	float mDamage = 10.0f;
	LLGP::Vector2f mDirection;

	float mLifetime = 5.0f;
	
};

