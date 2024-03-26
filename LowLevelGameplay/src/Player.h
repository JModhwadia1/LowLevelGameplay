#pragma once
#include "Vector2.h"
#include <SFML/Graphics.hpp>
#include "Transform.h"
#include "Rigidbody.h"
#include "GameObject.h"
#include "Animation.h"
#include "InputManager.h"

enum AnimationIndex
{
	WalkingUp,
	WalkingDown,
	WalkingLeft,
	WalkingRight,
	Count
};


class Player : public GameObject
{
public:
	explicit Player(sf::Texture& texture);

	void Update(float dt);
	void Render(sf::RenderWindow& window);

	LLGP::Vector2f direction;
	void UpdateMovement(LLGP::Vector2f _moveInput);
	float AccelerationSpeed = 200.0f;
	float mMaxSpeed = 300.0f;
private:
	Animation animations[int(AnimationIndex::Count)]; // 4 anims
	AnimationIndex currentAnimation = AnimationIndex::WalkingLeft;

};

