#include "Bullet.h"
#include <iostream>
#include "GameWorld.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include "Enemy.h"

GameWorld* GameWorld::world;

Bullet::Bullet() : GameObject(GameWorld::world->GetResources().mBulletTex)
{
	GetRigidbody()->SetMaxSpeed(mBulletSpeed);

	mBoxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(2.0f, 2.0f));
	mLineCollider = new LineCollider(GetTransform(),
		LLGP::Vector2f((GetTransform()->GetPosition().x + GetTexture2D()->GetSprite()->getScale().x), GetTransform()->GetPosition().y + GetTexture2D()->GetSprite()->getScale().y), // Head Point
		LLGP::Vector2f((GetTransform()->GetPosition().x - GetTexture2D()->GetSprite()->getScale().x), GetTransform()->GetPosition().y - GetTexture2D()->GetSprite()->getScale().y),*GetTexture2D()->GetSprite()); // Tail Point

	std::cout << GetTexture2D()->GetSprite()->getScale().x + GetTransform()->GetPosition().x << std::endl;

	SetCollider(mLineCollider);
}

void Bullet::Launch(const BulletLaunchParams* params)
{
	GetTransform()->SetPosition(params->mStartPos);
	//GetRigidbody()->SetVelocity((params->mDirection * mBulletSpeed).Normalised());
	mDirection = params->mDirection;

	mOwner = params->mOwner;
	mDamage = params->mDamage;
	GameObject::Draw(GameWorld::world->mWindow);
}

void Bullet::Start()
{
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
