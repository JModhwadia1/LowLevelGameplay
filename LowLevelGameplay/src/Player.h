#pragma once
#include "Vector2.h"
#include <SFML/Graphics.hpp>
//#include "Transform.h"
//#include "Rigidbody.h"
#include "GameObject.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "HealthComponent.h"
//#include "Event.h"

//class HealthComponent;

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

	virtual void Start() override;
	virtual void Update(float dt)override;
	void Draw(sf::RenderWindow* window)override;
	LLGP::Vector2f direction;
	LLGP::Vector2f mPrevDirection;
	void UpdateMovement(float dt);
	float AccelerationSpeed = 200.0f;
	float mMaxSpeed = 300.0f;
	void HandleOnDied(bool Die);

	void PrintHealth(float Amount);

	LLGP::Event<bool> OnPlayerDied;
	
private:
	Animation animations[int(AnimationIndex::Count)]; // 4 anims
	AnimationIndex currentAnimation = AnimationIndex::WalkingLeft;
	BoxCollider* _boxCollider;
	SphereCollider* _sphereCollider;

	float mShootCooldown;
	float mShootDelay = 0.1f;
	EFacingDirection mFacingDirection = EFacingDirection::FACING_LEFT;

	HealthComponent* healthcomp;


};

