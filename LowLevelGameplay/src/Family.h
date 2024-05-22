#pragma once

#include "GameObject.h"

class Player;
class BoxCollider;

enum States
{
	Idle,
	Wander,
	Death,
};

class Family : public GameObject
{
	

public:

	Family() = default;
	~Family();
	virtual void IdleState(){};
	virtual void WanderState(float dt) {};
	virtual void DeathState() {};
	virtual void Draw(sf::RenderWindow* window) {};
	virtual void Update(float dt) {};
	virtual void UpdateStates() {};
	void ChangeCurrentState(States state) { m_CurrentState = state; }
protected:
	States m_CurrentState = States::Idle;
	float m_MaxSpeed = 100.0f;
	BoxCollider* m_BoxCollider;
private:


	
};

