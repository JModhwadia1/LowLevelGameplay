#pragma once
#include "Vector2.h"
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "HealthComponent.h"



enum EFacingDirection {
	FACING_RIGHT,
	FACING_LEFT,
	FACING_UP,
	FACING_DOWN,
};

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
	explicit Player();
	~Player();

	void Start() override;
	void Update(float dt)override;
	void FixedUpdate(float fixedUpdate) override;
	void Draw(sf::RenderWindow* window)override;
	LLGP::Vector2f direction;
	LLGP::Vector2f mPrevDirection;
	void UpdateMovement(float dt);
	float AccelerationSpeed = 200.0f;
	float mMaxSpeed = 600.0f;
	void HandleOnDied(bool Die);

	void PrintHealth(float Amount);

	LLGP::Event<bool> OnPlayerDied;
	
private:
	Animation animations[int(AnimationIndex::Count)]; // 4 anims
	AnimationIndex currentAnimation = AnimationIndex::WalkingLeft;
	BoxCollider* _boxCollider;
	SphereCollider* _sphereCollider;

	float mShootCooldown;
	float mShootDelay = 1.0f;
	EFacingDirection mFacingDirection = EFacingDirection::FACING_LEFT;

	HealthComponent* healthcomp;

	sf::RectangleShape shape;
};

