#include "Bullet.h"
#include <iostream>
#include "GameWorld.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include "Enemy.h"




Bullet::Bullet()
{
	SetActive(false);
	Init(GameWorld::GetResources().mBulletTex);
	GetRigidbody()->SetMaxSpeed(mBulletSpeed);
	GetTransform()->SetPosition(LLGP::Vector2f(3000.0f, 1.0f));
	SetName("Grunts");
	mBoxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(GetTexture2D()->GetSprite()->getGlobalBounds().getSize().x, GetTexture2D()->GetSprite()->getGlobalBounds().getSize().y));
	mLineCollider = new LineCollider(GetTransform(), mDirection.Normalised(), -mDirection.Normalised(), *GetTexture2D()->GetSprite());
	std::cout << GetTexture2D()->GetSprite()->getScale().x + GetTransform()->GetPosition().x << std::endl;
	SetCollider(mLineCollider);
}

void Bullet::Launch(const BulletLaunchParams* params)
{
	GetTransform()->SetPosition(params->mStartPos);
	
	mDirection = params->mDirection;

	mOwner = params->mOwner;
	mDamage = params->mDamage;
	GameObject::Draw(GameWorld::mWindow);
}



void Bullet::OnCollision(GameObject& other)
{
	/*if (!GetIsActive()) return;*/
	if (other.uuid == mOwner->uuid) return;
	if (Enemy* enemy = static_cast<Enemy*>(&other)) {
		enemy->ApplyDamage(this, mDamage);

		std::cout << "hit enemy" << std::endl;
	}
		
}

void Bullet::Update(float dt)
{
	if (!GetIsActive()) return;
	mLifetime -= dt;

	// Set itself to false - not sure if works with object pooler tho
	if (mLifetime <= 0) {
		mLifetime = 5.0f;
		SetActive(false);
	}

}

void Bullet::FixedUpdate(float fixedDeltatime) 
{
	if (!GetIsActive()) return;
	GetRigidbody()->SetVelocity(mDirection * mBulletSpeed);
	GetRigidbody()->Update(fixedDeltatime);
}

void Bullet::Draw(sf::RenderWindow* window) {
	if (!GetIsActive()) return;
	GameObject::Draw(window);
}
