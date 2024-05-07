#include "FamilyMan.h"
#include "GameWorld.h"
#include "BoxCollider.h"
#include <iostream>

FamilyMan::FamilyMan() : Family(GameWorld::GetResources().mMenTex)
{
	m_MaxSpeed = 100.0f;
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
	
	m_NewPointGenTime -= dt;

	if (m_NewPointGenTime <= 0) {
		m_NewPointGenTime = 2.0f;
		randomPoint = GameWorld::GetRandomPosInArena();
		/*std::cout << "X: " << randomPoint.x << "Y: " << randomPoint.y << std::endl;*/
		
	}
	
	if (GetTransform()->GetPosition() == randomPoint && !m_NewPointGenTime <= 0 ) 
	{
		randomPoint = GameWorld::GetRandomPosInArena();
	}

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

	GameObject::Update(dt);
}

void FamilyMan::UpdateStates()
{
	
}
