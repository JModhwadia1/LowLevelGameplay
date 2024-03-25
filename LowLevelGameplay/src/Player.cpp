#include "Player.h"
#include <iostream>
#include <SFML/Window/Mouse.hpp>



Player::Player(sf::Texture& texture) : GameObject(texture)
{
	//mSprite = sf::Sprite(texture);
	// Setup Transform
	/*_transform = new Transform(LLGP::Vector2f(250, 250), LLGP::Vector2f(5, 5));
	mSprite.setPosition(_transform->GetPosition());
	mSprite.setScale(_transform->GetScale());*/

	//Setup Rigidbody
	//_rigidbody = new Rigidbody(_transform);
	GetRigidbody()->SetMaxSpeed(mMaxSpeed);
	GetTexture2D()->GetSprite()->setScale(5, 5);
	GetTexture2D()->GetSprite()->setTextureRect(sf::IntRect(0,0,5,11));

	animations[int(AnimationIndex::WalkingUp)] = Animation(23, 0, 7, 12,"Textures/Player.png");
	animations[int(AnimationIndex::WalkingDown)] = Animation(14, 0, 7, 12, "Textures/Player.png");
	animations[int(AnimationIndex::WalkingLeft)] = Animation(0, 0, 5, 12, "Textures/Player.png");
	animations[int(AnimationIndex::WalkingRight)] = Animation(7, 0, 5, 12, "Textures/Player.png");



}

void Player::Update(float dt)
{


	
	UpdateMovement(dt);
	animations[int(currentAnimation)].Update(dt);
	animations[int(currentAnimation)].ApplyToSprite(*GetTexture2D()->GetSprite());
	GameObject::Update(dt);
	

	
}

void Player::Render(sf::RenderWindow& window)
{
	//window.draw(mSprite);
	GameObject::Draw(window);
}

void Player::UpdateMovement(float dt)
{
	LLGP::Vector2f accel(0.0f, 0.0f);
	direction = LLGP::Vector2f(0.0f, 0.0f);
	//_rigidbody->SetDirection(direction);
	GetRigidbody()->SetDirection(direction);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction.y -= 1.0f;
		//_rigidbody->SetDirection(direction);
		GetRigidbody()->SetDirection(direction);
		currentAnimation = AnimationIndex::WalkingUp;
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction.y += 1.0f;
		//_rigidbody->SetDirection(direction);
		GetRigidbody()->SetDirection(direction);
		currentAnimation = AnimationIndex::WalkingDown;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction.x += 1.0f;
		//_rigidbody->SetDirection(direction);
		GetRigidbody()->SetDirection(direction);
		currentAnimation = AnimationIndex::WalkingRight;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction.x -= 1.0f;
		//_rigidbody->SetDirection(direction);
		GetRigidbody()->SetDirection(direction);
		currentAnimation = AnimationIndex::WalkingLeft;

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
