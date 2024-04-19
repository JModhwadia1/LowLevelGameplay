#include "Bullet.h"
#include <iostream>
#include "GameWorld.h"

Bullet::Bullet(GameWorld* world, sf::Texture* texture) : GameObject(world, texture)
{
	GetRigidbody()->SetMaxSpeed(mBulletSpeed);
	
}

void Bullet::Launch(const BulletLaunchParams* params)
{
	GetTransform()->SetPosition(params->mStartPos);
	//GetRigidbody()->SetVelocity((params->mDirection * mBulletSpeed).Normalised());
	mDirection = params->mDirection;

	mOwner = params->mOwner;
	mDamage = params->mDamage;
	GameObject::Draw(GetWorld().mWindow);
}

void Bullet::OnCollision(GameObject& other)
{
	std::cout << "Bullet Collided " << std::endl;
}

void Bullet::Update(float dt)
{
	GetRigidbody()->AddForce(mDirection * mBulletSpeed);
	GameObject::Update(dt);
}

void Bullet::Draw(sf::RenderWindow* window) {

	GameObject::Draw(window);
}
