#include "Player.h"
#include <iostream>
#include "Bullet.h"
#include "GameWorld.h"
#include "ObjectPool.h"
#include <SFML/Window/Mouse.hpp>



Player::Player() : GameObject(GameWorld::GetResources().mPlayerTex)
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


	animations[int(AnimationIndex::WalkingUp)] = Animation(23, 0, 7, 12,"Textures/Player.png",*GameWorld::GetResources().mPlayerTex);
	animations[int(AnimationIndex::WalkingDown)] = Animation(14, 0, 7, 12, "Textures/Player.png", *GameWorld::GetResources().mPlayerTex);
	animations[int(AnimationIndex::WalkingLeft)] = Animation(0, 0, 5, 12, "Textures/Player.png",*GameWorld::GetResources().mPlayerTex);
	animations[int(AnimationIndex::WalkingRight)] = Animation(7, 0, 5, 12, "Textures/Player.png",*GameWorld::GetResources().mPlayerTex);

	// set prev direction to the facing direction of the player when spanwed (which is left)
	mPrevDirection = LLGP::Vector2f(-1.0f, 0.0f);
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
	
	shape.setSize(_boxCollider->GetHalfExtents());
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(3.0f);
	shape.setOutlineColor(sf::Color::Red);
	shape.setPosition(GetTransform()->GetPosition());
	


	
}

void Player::FixedUpdate(float fixedUpdate)
{
	GetRigidbody()->SetVelocity(direction * mMaxSpeed);
	GetRigidbody()->Update(fixedUpdate);
}

void Player::Draw(sf::RenderWindow* window)
{
	//window.draw(mSprite);
	GameObject::Draw(window);
	window->draw(shape);
}

void Player::UpdateMovement(float dt)
{
	direction = LLGP::Vector2f(0.0f, 0.0f);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mFacingDirection = FACING_UP;
		direction.y -= 1.0f;
		currentAnimation = AnimationIndex::WalkingUp;
	}
	

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mFacingDirection = FACING_DOWN;
		direction.y += 1.0f;
		currentAnimation = AnimationIndex::WalkingDown;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mFacingDirection = FACING_RIGHT;
		direction.x += 1.0f;
		currentAnimation = AnimationIndex::WalkingRight;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mFacingDirection = FACING_LEFT;
		direction.x -= 1.0f;
		currentAnimation = AnimationIndex::WalkingLeft;

	}
	mPrevDirection = direction;
	
	mShootCooldown -= dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {


		if (mShootCooldown <= 0) {

			mShootCooldown = mShootDelay;

			BulletLaunchParams params;
			params.mOwner = this;
			params.mStartPos = GetTransform()->GetPosition();
			params.mDirection = mPrevDirection;
			params.mDamage = 10.0f;

			if (Bullet* bullet = ObjectPool::GetPooledObjectAsType<Bullet>("Bullet"))
			{
				bullet->Launch(&params);
				std::cout << "Bullet spawned" << std::endl;
			}

			/*if (Bullet* bullet = ObjectPool::GetPooledObject("Bullet"))
			{

			}*/
		}
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
	
		healthcomp->TakeDamage(nullptr,10.0f);
	}

	
	
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
