#pragma once
#include "GameObject.h"
#include "Player.h"
#include "BoxCollider.h"
#include "SphereCollider.h"


enum States
{
	Idle,
	Chase,
	Attack,
	Death
};

class Enemy : public GameObject
{
public:
	Enemy(sf::Texture& texture);


	void ChangeCurrentState(States state) { _currentState = state; }
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void IdleState();
	void ChaseState();
	void AttackState();
	void DeathState();
	void UpdateStates();
	void SetPlayerRef(Player* player) { _playerRef = player; }

protected:
	States _currentState = States::Idle;
private:
	Player* _playerRef = nullptr;
	float AttackDistance = 50.0f;
	BoxCollider* _boxCollider;
	SphereCollider* _sphereCollider;


};

