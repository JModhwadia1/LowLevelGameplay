#include "Player.h"
#include <iostream>


Player::Player(sf::Texture& texture) : Entity(texture)
{
	//mSprite = sf::Sprite(texture);
	// Setup Transform
	/*_transform = new Transform(LLGP::Vector2f(250, 250), LLGP::Vector2f(5, 5));
	mSprite.setPosition(_transform->GetPosition());
	mSprite.setScale(_transform->GetScale());*/

	//Setup Rigidbody
	//_rigidbody = new Rigidbody(_transform);
	GetRigidbody()->SetMaxSpeed(1000.0f);
	

}

void Player::Update(float dt)
{

	UpdateMovement(dt);
	Entity::Update(dt);
	
}

void Player::Render(sf::RenderWindow& window)
{
	//window.draw(mSprite);
	Entity::Draw(window);
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
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction.y += 1.0f;
		//_rigidbody->SetDirection(direction);
		GetRigidbody()->SetDirection(direction);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction.x += 1.0f;
		//_rigidbody->SetDirection(direction);
		GetRigidbody()->SetDirection(direction);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction.x -= 1.0f;
		//_rigidbody->SetDirection(direction);
		GetRigidbody()->SetDirection(direction);
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
