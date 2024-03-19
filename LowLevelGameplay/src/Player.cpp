#include "Player.h"

Player::Player(const sf::Texture& texture)
{
	mSprite = sf::Sprite(texture);
	mSprite.setScale(5, 5);
}

void Player::Update(float dt)
{
	UpdateMovement(dt);
	mVelocity += mAcceleration * dt;

	mVelocity = direction * mMaxSpeed;
	 //Clamp Speed
	/*if (LLGP::LengthSq(mVelocity) > (mMaxSpeed * mMaxSpeed))
	{
		mVelocity.Normalised();
		mVelocity *= mMaxSpeed;
	}*/

	/*if (((mVelocity.x * mVelocity.x) + (mVelocity.y * mVelocity.y)) > (mMaxSpeed * mMaxSpeed))
	{
		mVelocity = mVelocity.Normalised();
		mVelocity *= mMaxSpeed;
	}*/

	mPosition += mVelocity * dt;
	mSprite.setPosition(mPosition);
}

void Player::Render(sf::RenderWindow& window)
{
	window.draw(mSprite);
}

void Player::UpdateMovement(float dt)
{
	LLGP::Vector2f accel(0.0f, 0.0f);
	direction = LLGP::Vector2f(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction.y -= 1.0f;
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction.y += 1.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction.x += 1.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction.x -= 1.0f;
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
