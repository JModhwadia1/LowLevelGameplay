#pragma once
#include "Vector2.h"
#include <SFML/Graphics.hpp>
#include "Transform.h"
#include "Rigidbody.h"
class Player
{
public:
	explicit Player(const sf::Texture& texture);

	void Update(float dt);
	void Render(sf::RenderWindow& window);


	void UpdateMovement(float dt);
	float AccelerationSpeed = 200.0f;
	float mMaxSpeed = 300.0f;

	sf::Sprite mSprite;
	LLGP::Vector2f mAcceleration = LLGP::Vector2f(0.0f, 0.0f);
	LLGP::Vector2f mVelocity = LLGP::Vector2f(0.0f, 0.0f);
	LLGP::Vector2f mPosition = LLGP::Vector2f(0.0f, 0.0f);
	
	LLGP::Vector2f direction;
	

	Transform* _transform;
	Rigidbody* _rigidbody;

};

