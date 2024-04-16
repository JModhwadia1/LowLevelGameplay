#include "Bullet.h"

Bullet::Bullet(GameWorld* world, sf::Texture* texture) : GameObject(world, texture)
{
	GetRigidbody()->SetMaxSpeed(mBulletSpeed);
	
}

void Bullet::Launch(const BulletLaunchParams* params)
{
	GetTransform()->SetPosition(params->mStartPos);
	GetRigidbody()->SetVelocity((params->mDirection * mBulletSpeed).Normalised());

	mOwner = params->mOwner;
	mDamage = params->mDamage;
}

void Bullet::OnCollision(GameObject& other)
{
	std::cout << "Bullet Collided " << std::endl;
}
