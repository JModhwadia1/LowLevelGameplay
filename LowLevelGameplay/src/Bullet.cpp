#include "Bullet.h"
#include <iostream>
#include "GameWorld.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include "SphereCollider.h"
#include "Enemy.h"




Bullet::Bullet() : GameObject(GameWorld::GetResources().mBulletTex)
{
	GetRigidbody()->SetMaxSpeed(mBulletSpeed);

	mBoxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(GetTexture2D()->GetSprite()->getGlobalBounds().getSize().x, GetTexture2D()->GetSprite()->getGlobalBounds().getSize().y));
	mLineCollider = new LineCollider(GetTransform(), mDirection.Normalised() * 2.0f, -mDirection.Normalised() * 2.0f, *GetTexture2D()->GetSprite());
	mSphereCollider = new SphereCollider(GetTransform(), 15.0f);
	
	//SetActive(true);
	SetCollider(mBoxCollider);
}

void Bullet::Launch(const BulletLaunchParams* params)
{
	GetTransform()->SetPosition(params->mStartPos);
	
	mDirection = params->mDirection;

	mOwner = params->mOwner;
	mDamage = params->mDamage;
	GameObject::Draw(GameWorld::mWindow);
}

void Bullet::Start()
{
}

void Bullet::OnCollision(GameObject& other)
{
	if (!GetIsActive()) return;
	if (other.uuid == mOwner->uuid) return;
	if (Enemy* enemy = dynamic_cast<Enemy*>(&other)) {
		enemy->ApplyDamage(this, mDamage);
		
		/*GameWorld::RemoveFromGameobject(enemy);*/
		//delete enemy;
		//enemy = nullptr;
		////enemy->SetActive(false);
		//SetActive(false);
		
	}
		
}

void Bullet::Update(float dt)
{
	if (!GetIsActive()) return;
	mLifetime -= dt;

	if (mLifetime <= 0) {
		SetActive(false);
		mLifetime = 2.0f;
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
