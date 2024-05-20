#pragma once
#include "Enemy.h"
class Hulks : public Enemy
{
public:
	Hulks(sf::Texture* texture);
	~Hulks();
	void Start() override;
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
	LLGP::Vector2f randomPoint;

	float m_NewPointGenTime = 2.0f;
};

