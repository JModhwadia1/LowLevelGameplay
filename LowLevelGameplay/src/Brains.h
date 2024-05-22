#pragma once
#include "Enemy.h"
class Brains : public Enemy
{
public:
	Brains();
	~Brains();
	
	void ChangeCurrentState(States state) { _currentState = state; }
	void Update(float dt)override;
	void FixedUpdate(float fixedUpdate) override;
	void Draw(sf::RenderWindow* window)override;
	void IdleState();
	void ChaseState();
	void AttackState();
	void DeathState();
	void UpdateStates();
	void SetPlayerRef(Player* player) { _playerRef = player; }
	void HandleOnDied(bool die);
	void HandlePlayerDied(bool die);
	void OnCollision(GameObject& other) override;
private:
	float mShootCooldown = 0.0f;
	float mShootDelay = 1.0f;
};

