#pragma once
#include "Vector2.h"
#include <SFML/Graphics.hpp>
#include "Transform.h"
#include "Rigidbody.h"
#include "Entity.h"
class Player : public Entity
{
public:
	explicit Player(sf::Texture& texture);

	void Update(float dt);
	void Render(sf::RenderWindow& window);

	LLGP::Vector2f direction;
	void UpdateMovement(float dt);
	float AccelerationSpeed = 200.0f;
	float mMaxSpeed = 300.0f;
		

};

