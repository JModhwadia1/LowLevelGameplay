#include "FamilyMan.h"
#include "GameWorld.h"
#include "BoxCollider.h"
#include <iostream>

FamilyMan::FamilyMan() 
{
	Init(GameWorld::GetResources().mMenTex);
	m_MaxSpeed = 10.0f;
	GetRigidbody()->SetMaxSpeed(m_MaxSpeed);
	m_BoxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(25.0f, 55.0f));
	SetCollider(m_BoxCollider);
	GetTransform()->SetPosition(LLGP::Vector2f(960, 540));
	GetTexture2D()->GetSprite()->setScale(5, 5);
	randomPoint = GameWorld::GetRandomPosInArena();
	ChangeCurrentState(States::Wander);
}

FamilyMan::~FamilyMan()
{

}

void FamilyMan::IdleState()
{

}

void FamilyMan::WanderState(float dt)
{
	
	// reduce timer counter
	m_NewPointGenTime -= dt;
	// if time is below 0 
	if (m_NewPointGenTime <= 0) {
		// reset time
		m_NewPointGenTime = 2.0f;
		// gen a new position
		randomPoint = GameWorld::GetRandomPosInArena();
	}
	// if we have reached the position before timer ended
	if (GetTransform()->GetPosition() == randomPoint && !m_NewPointGenTime <= 0 ) 
	{
		// get a random pos
		randomPoint = GameWorld::GetRandomPosInArena();
	}
	// set direction
	LLGP::Vector2f direction = randomPoint - GetTransform()->GetPosition();
	GetRigidbody()->AddForce(direction.Normalised() * m_MaxSpeed);
}

void FamilyMan::DeathState()
{

}

void FamilyMan::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
}

void FamilyMan::Update(float dt)
{
	UpdateStates();

	switch (m_CurrentState)
	{
	case Idle:
		IdleState();
		break;
	case Wander:
		WanderState(dt);
		break;
	case Death:
		DeathState();
		break;
	default:
		break;
	}

	
}

void FamilyMan::UpdateStates()
{
	
}
