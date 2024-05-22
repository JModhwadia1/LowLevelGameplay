#pragma once
#include "GameObject.h"

class Player;
class BoxCollider;
class SphereCollider;
class HealthComponent;


class Enemy : public GameObject
{
protected:
	enum States
	{
		Idle,
		Chase,
		Attack,
		Death
	};

public:

	Enemy() = default;

	
	void ChangeCurrentState(States state) { _currentState = state; }
	virtual void Update(float dt)override;
	virtual void FixedUpdate(float FixedDeltatime) override;
	virtual void Draw(sf::RenderWindow* window)override;
	virtual void IdleState();
	virtual void ChaseState();
	virtual void AttackState();
	virtual void DeathState();
	virtual void UpdateStates();
	void SetPlayerRef(Player* player) { _playerRef = player; }


	virtual void OnCollision(GameObject& other) override;
	LLGP::Event<bool,int> OnEnemyDied;

protected:
	States _currentState = States::Idle;
	float mMaxSpeed = 5.0f;
	Player* _playerRef = nullptr;
	float AttackDistance = 50.0f;
	BoxCollider* _boxCollider;
	SphereCollider* _sphereCollider;
	HealthComponent* _healthComponent;
	sf::RectangleShape shape;
	// Get direction
	LLGP::Vector2f direction;
	int pointsToGive = 0;

};

