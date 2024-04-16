#include "Player.h"
#include <iostream>
#include "Bullet.h"
#include <SFML/Window/Mouse.hpp>



Player::Player(GameWorld* world, sf::Texture* texture) : GameObject(world, texture)
{
	
	GetRigidbody()->SetMaxSpeed(mMaxSpeed);
	GetTexture2D()->GetSprite()->setScale(5, 5);
	GetTexture2D()->GetSprite()->setTextureRect(sf::IntRect(0,0,5,11));
	_boxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(25.0f, 55.0f));
	_sphereCollider = new SphereCollider(GetTransform(), 20.0f);
	SetCollider(_boxCollider);

	animations[int(AnimationIndex::WalkingUp)] = Animation(23, 0, 7, 12,"Textures/Player.png",*texture);
	animations[int(AnimationIndex::WalkingDown)] = Animation(14, 0, 7, 12, "Textures/Player.png",*texture);
	animations[int(AnimationIndex::WalkingLeft)] = Animation(0, 0, 5, 12, "Textures/Player.png",*texture);
	animations[int(AnimationIndex::WalkingRight)] = Animation(7, 0, 5, 12, "Textures/Player.png",*texture);



}

void Player::Update(float dt)
{
	UpdateMovement(dt);
	animations[int(currentAnimation)].Update(dt);
	animations[int(currentAnimation)].ApplyToSprite(*GetTexture2D()->GetSprite());
	GameObject::Update(dt);
	
}

void Player::Render(sf::RenderWindow* window)
{
	//window.draw(mSprite);
	GameObject::Draw(window);
}

void Player::UpdateMovement(float dt)
{
	LLGP::Vector2f accel(0.0f, 0.0f);
	direction = LLGP::Vector2f(0.0f, 0.0f);
	

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction.y -= 1.0f;
		GetRigidbody()->AddForce(direction * mMaxSpeed);
		currentAnimation = AnimationIndex::WalkingUp;
		
	}
	

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
	
		direction.y += 1.0f;
		GetRigidbody()->AddForce(direction * mMaxSpeed);
		currentAnimation = AnimationIndex::WalkingDown;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction.x += 1.0f;
		GetRigidbody()->AddForce(direction * mMaxSpeed);
		currentAnimation = AnimationIndex::WalkingRight;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		
		direction.x -= 1.0f;
		GetRigidbody()->AddForce(direction * mMaxSpeed);
		currentAnimation = AnimationIndex::WalkingLeft;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

		BulletLaunchParams params;
		params.mOwner = this;
		params.mStartPos = GetTransform()->GetPosition() * 2.0f;
		params.mDirection = direction * 2.0f;
		params.mDamage = 10.0f;

		sf::Texture* bulletTex = new sf::Texture();

		if (!bulletTex->loadFromFile("Textures/player.png", sf::IntRect(14, 0, 7, 12)))
		{
			std::cout << "Bullet texture cannot be loaded" << std::endl;
		}

		Bullet* bullet = new Bullet(GetWorld(), bulletTex);
		bullet->Launch(&params);

		std::cout << bullet->GetTransform()->GetPosition().x << std::endl;
	}
	

	

	//if ((((accel.x * accel.x) + (accel.y * accel.y)) > 0.0f))
	//{
	//	accel = accel.Normalised();
	//	accel *= AccelerationSpeed;

	//	mAcceleration = accel;

	//	//SetAcceleration(accel);
	//}
	//else
	//{
	//	mAcceleration = mVelocity * -1.0f;
	//}
}
