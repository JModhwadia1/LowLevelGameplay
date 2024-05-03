#include "Player.h"
#include <iostream>
#include "Bullet.h"
#include "GameWorld.h"
#include <SFML/Window/Mouse.hpp>



Player::Player(GameWorld* world, sf::Texture* texture) : GameObject(world, texture)
{
	
	GetRigidbody()->SetMaxSpeed(mMaxSpeed);
	GetTexture2D()->GetSprite()->setScale(5, 5);
	GetTexture2D()->GetSprite()->setTextureRect(sf::IntRect(0,0,5,11));
	_boxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(25.0f, 55.0f));
	_sphereCollider = new SphereCollider(GetTransform(), 20.0f);
	SetCollider(_boxCollider);

	healthcomp = new HealthComponent(this);
	healthcomp->OnHealthUpdated += std::bind(&Player::PrintHealth, this, std::placeholders::_1);
	healthcomp->OnDied += std::bind(&Player::HandleOnDied, this, std::placeholders::_1);


	animations[int(AnimationIndex::WalkingUp)] = Animation(23, 0, 7, 12,"Textures/Player.png",*texture);
	animations[int(AnimationIndex::WalkingDown)] = Animation(14, 0, 7, 12, "Textures/Player.png",*texture);
	animations[int(AnimationIndex::WalkingLeft)] = Animation(0, 0, 5, 12, "Textures/Player.png",*texture);
	animations[int(AnimationIndex::WalkingRight)] = Animation(7, 0, 5, 12, "Textures/Player.png",*texture);


}

Player::~Player()
{
	healthcomp->OnHealthUpdated -= std::bind(&Player::PrintHealth, this, std::placeholders::_1);
	healthcomp->OnDied -= std::bind(&Player::HandleOnDied, this, std::placeholders::_1);
	
	healthcomp = nullptr;
	_boxCollider = nullptr;
	_sphereCollider = nullptr;

}

void Player::Start()
{
}

void Player::Update(float dt)
{
	UpdateMovement(dt);
	animations[int(currentAnimation)].Update(dt);
	animations[int(currentAnimation)].ApplyToSprite(*GetTexture2D()->GetSprite());
	GameObject::Update(dt);
	


	
}

void Player::Draw(sf::RenderWindow* window)
{
	//window.draw(mSprite);
	GameObject::Draw(window);
}

void Player::UpdateMovement(float dt)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mFacingDirection = FACING_UP;
		direction.y -= 1.0f;
		currentAnimation = AnimationIndex::WalkingUp;
		mPrevDirection = direction;
	}
	

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mFacingDirection = FACING_DOWN;
		direction.y += 1.0f;
		currentAnimation = AnimationIndex::WalkingDown; 
		mPrevDirection = direction;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mFacingDirection = FACING_RIGHT;
		direction.x += 1.0f;
		currentAnimation = AnimationIndex::WalkingRight;
		mPrevDirection = direction;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mFacingDirection = FACING_LEFT;
		direction.x -= 1.0f;
		currentAnimation = AnimationIndex::WalkingLeft;
		mPrevDirection = direction;

	}
	
	mShootCooldown -= dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {


		if (mShootCooldown <= 0) {

			mShootCooldown = mShootDelay;

			BulletLaunchParams params;
			params.mOwner = this;
			params.mStartPos = GetTransform()->GetPosition();
			params.mDirection = mPrevDirection;
			params.mDamage = 10.0f;

			if (Bullet* bullet = GetWorld().SpawnGameobject<Bullet>(GetWorld().GetResources().mBulletTex)) 
			{
				bullet->Launch(&params);
			}
		}
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
	
		healthcomp->TakeDamage(nullptr,10.0f);
	}


	GetRigidbody()->AddForce(direction * mMaxSpeed);
	direction = LLGP::Vector2f(0.0f, 0.0f);
}

void Player::HandleOnDied(bool Die)
{
	if (Die)
	{
		OnPlayerDied(Die);
	}
}

void Player::PrintHealth(float Amount)
{
	std::cout << "Amount" << Amount << std::endl;
}
