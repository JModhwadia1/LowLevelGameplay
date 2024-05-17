#include "Bullet.h"
#include <iostream>
#include "GameWorld.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include "Enemy.h"




Bullet::Bullet() : GameObject(GameWorld::GetResources().mBulletTex)
{
	GetRigidbody()->SetMaxSpeed(mBulletSpeed);

	mBoxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(2.0f, 2.0f));
	mLineCollider = new LineCollider(GetTransform(), mDirection.Normalised(), -mDirection.Normalised(),
	std::cout << GetTexture2D()->GetSprite()->getScale().x + GetTransform()->GetPosition().x << std::endl;
	SetActive(true);
	SetCollider(mBoxCollider);
}

void Bullet::Launch(const BulletLaunchParams* params)
{
	GetTransform()->SetPosition(params->mStartPos);
	//GetRigidbody()->SetVelocity((params->mDirection * mBulletSpeed).Normalised());
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


	if (Enemy* enemy = dynamic_cast<Enemy*>(&other)) {
		std::cout << "Bullet Collided with enemy" << std::endl;

	}
		
}

void Bullet::Update(float dt)
{
	/*GetRigidbody()->AddForce(mDirection * mBulletSpeed);*/

}

void Bullet::FixedUpdate(float fixedDeltatime) 
{
	GetRigidbody()->SetVelocity(mDirection * mBulletSpeed);
	GetRigidbody()->Update(fixedDeltatime);
}

void Bullet::Draw(sf::RenderWindow* window) {

	GameObject::Draw(window);
}
