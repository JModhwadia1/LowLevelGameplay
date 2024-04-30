#pragma once
#include "GameObject.h"
//#include "Player.h"


class Player;
class BoxCollider;
class SphereCollider;



class Enemy : public GameObject
{
	enum States
	{
		Idle,
		Chase,
		Attack,
		Death
	};

public:
	Enemy(GameWorld* world,sf::Texture* texture);


	void ChangeCurrentState(States state) { _currentState = state; }
	void Update(float dt)override;
	void Draw(sf::RenderWindow* window)override;
	void IdleState();
	void ChaseState();
	void AttackState();
	void DeathState();
	void UpdateStates();
	void SetPlayerRef(Player* player) { _playerRef = player; }


	void OnCollision(GameObject& other) override;

protected:
	States _currentState = States::Idle;
private:
	float mMaxSpeed = 100.0f;
	Player* _playerRef = nullptr;
	float AttackDistance = 50.0f;
	BoxCollider* _boxCollider;
	SphereCollider* _sphereCollider;

	


};

