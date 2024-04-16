#pragma once
#include "GameObject.h"

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
	Bullet(GameWorld* world, sf::Texture* texture);
	void Launch(const BulletLaunchParams* params);

	const GameObject* GetOwner() const { return mOwner ? mOwner : this; }
	float GetDamage() const { return mDamage; }
	float GetBulletSpeed() { return mBulletSpeed; }

	void OnCollision(GameObject& other) override;

private:
	float mBulletSpeed = 20.0f;
	const GameObject* mOwner = nullptr;
	float mDamage = 10.0f;
	
};

