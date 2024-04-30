#include "Bullet.h"
#include <iostream>
#include "GameWorld.h"
#include "BoxCollider.h"
#include "Enemy.h"

Bullet::Bullet(GameWorld* world, sf::Texture* texture) : GameObject(world, world->GetResources().mBulletTex)
{
	GetRigidbody()->SetMaxSpeed(mBulletSpeed);

	mBoxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(2.0f, 2.0f));

	SetCollider(mBoxCollider);

	
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

	if (Enemy* enemy = dynamic_cast<Enemy*>(&other)) {

		std::cout << "Bullet Collided with enemy" << std::endl;
	}
}

void Bullet::Update(float dt)
{
	
	GetRigidbody()->AddForce(mDirection * mBulletSpeed);
	GameObject::Update(dt);
}

void Bullet::Draw(sf::RenderWindow* window) {

	GameObject::Draw(window);
}
