#include "Player.h"
#include <iostream>
#include "Bullet.h"
#include "GameWorld.h"
#include "Grunts.h"
#include "ObjectPool.h"
#include <SFML/Window/Mouse.hpp>



Player::Player() 
{
	Init(GameWorld::GetResources().mPlayerTex);
	SetActive(true);
	GetRigidbody()->SetMaxSpeed(mMaxSpeed);
	GetTexture2D()->GetSprite()->setScale(5, 5);
	GetTexture2D()->GetSprite()->setTextureRect(sf::IntRect(0,0,5,11));
	_boxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(25.0f, 55.0f));
	_sphereCollider = new SphereCollider(GetTransform(), 20.0f);
	SetCollider(_sphereCollider);

	healthcomp = new HealthComponent(this);
	healthcomp->OnHealthUpdated.AddListener(this, std::bind(&Player::PrintHealth, this, std::placeholders::_1));
	healthcomp->OnDied.AddListener(this, std::bind(&Player::HandleOnDied, this, std::placeholders::_1));
	SetName("Player");

	animations[int(AnimationIndex::WalkingUp)] = Animation(23, 0, 7, 12,"Textures/Player.png",*GameWorld::GetResources().mPlayerTex);
	animations[int(AnimationIndex::WalkingDown)] = Animation(14, 0, 7, 12, "Textures/Player.png", *GameWorld::GetResources().mPlayerTex);
	animations[int(AnimationIndex::WalkingLeft)] = Animation(0, 0, 5, 12, "Textures/Player.png",*GameWorld::GetResources().mPlayerTex);
	animations[int(AnimationIndex::WalkingRight)] = Animation(7, 0, 5, 12, "Textures/Player.png",*GameWorld::GetResources().mPlayerTex);

	// set prev direction to the facing direction of the player when spanwed (which is left)
	mPrevDirection = LLGP::Vector2f(-1.0f, 0.0f);

	
	if (!bulletBuffer.loadFromFile("Textures/Bullet.wav")) {
		std::cout << "cant load bullet buffer. Player.cpp" << std::endl;
	}
}

Player::~Player()
{
	
	healthcomp->OnHealthUpdated.RemoveListener(this, std::bind(&Player::PrintHealth, this, std::placeholders::_1));
	healthcomp->OnDied.RemoveListener(this,  std::bind(&Player::HandleOnDied, this, std::placeholders::_1));
	
	delete(_boxCollider);
	delete(_sphereCollider);
	delete(healthcomp);
	_boxCollider = nullptr;
	_sphereCollider = nullptr;
	healthcomp = nullptr;
	
}



void Player::Update(float dt)
{
	UpdateMovement(dt);
	animations[int(currentAnimation)].Update(dt);
	animations[int(currentAnimation)].ApplyToSprite(*GetTexture2D()->GetSprite());
	

	
	if (isInvincible) {
		invinciblityDuration -= dt;

		if (invinciblityDuration <= 0.0f) 
		{
			invinciblityDuration = 2.0f;
			isInvincible = false;
		}
		
	}

	
}

void Player::FixedUpdate(float fixedUpdate)
{
	GetRigidbody()->SetVelocity(direction * mMaxSpeed);
	GetRigidbody()->Update(fixedUpdate);
}

void Player::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
	window->draw(shape);
}

void Player::UpdateMovement(float dt)
{
	direction = LLGP::Vector2f((float)(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) - (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)),
		(float)(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) - (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)));
	//direction.Normalise();

	if (direction != LLGP::Vector2f(0, 0)) {

		mPrevDirection = direction;
	}
	
	switch ((int)direction.x)
	{
	case 1:
		mFacingDirection = FACING_RIGHT;
		break;
	case -1:
		mFacingDirection = FACING_LEFT;
		break;
	default:
		break;
	}

	switch ((int)direction.y)
	{
	case 1:
		mFacingDirection = FACING_UP;
		break;
	case -1:
		mFacingDirection = FACING_DOWN;
		break;
	default:
		break;
	}

	switch (mFacingDirection)
	{
	case FACING_RIGHT:
		currentAnimation = AnimationIndex::WalkingRight;
		break;
	case FACING_LEFT:
		currentAnimation = AnimationIndex::WalkingLeft;
		break;
	case FACING_UP:
		currentAnimation = AnimationIndex::WalkingUp;
		break;
	case FACING_DOWN:
		currentAnimation = AnimationIndex::WalkingDown;
		break;
	default:
		break;
	}
	
	mShootCooldown -= dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {


		if (mShootCooldown <= 0) {

			mShootCooldown = mShootDelay;

			BulletLaunchParams params;
			params.mOwner = this;
			params.mStartPos = GetTransform()->GetPosition();
			params.mDirection = mPrevDirection;
			params.mDamage = 1000.0f;

			// Object pooler way
			if (Bullet* bullet = ObjectPool::GetPooledObjectAsType<Bullet>("Bullet"))
			{
				bullet->Launch(&params);
				bulletSound.setBuffer(bulletBuffer);
				bulletSound.play();
				std::cout << "Bullet spawned" << std::endl;
			}
		}
		
		
	}

	

	
	
}

void Player::HandleOnDied(bool Die)
{
	if (Die && !isInvincible)
	{
		OnPlayerDied(Die);
	}
}

void Player::PrintHealth(float Amount)
{
	/*std::cout << "Amount" << Amount << std::endl;*/
}

void Player::OnCollision(GameObject& other) 
{

	
	
}
