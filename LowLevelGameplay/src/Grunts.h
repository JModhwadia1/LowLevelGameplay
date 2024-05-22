#pragma once
#include "Enemy.h"
#include "Event.h"
class Grunts : public Enemy
{
public:
	Grunts();
	~Grunts();
	
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

};

