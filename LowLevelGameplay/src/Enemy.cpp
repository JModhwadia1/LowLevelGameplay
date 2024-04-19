#include "Enemy.h"
#include "Player.h"
#include "GameWorld.h"
#include <iostream>

Enemy::Enemy(GameWorld* world, sf::Texture* texture) : GameObject(world, texture)
{

	GetRigidbody()->SetMaxSpeed(mMaxSpeed);
	GetTexture2D()->GetSprite()->setScale(5, 5);
	GetTexture2D()->GetSprite()->setTextureRect(sf::IntRect(0, 0, 5, 11));
	GetTransform()->SetPosition(LLGP::Vector2f(100.f, 100.f));
	_boxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(25.0f, 55.0f));
	_sphereCollider = new SphereCollider(GetTransform(), 20.0f);
	SetCollider(_sphereCollider);
	_playerRef = GetWorld().GetPlayer();
}

void Enemy::Update(float dt)
{
	UpdateStates();

	switch (_currentState)
	{
	case Idle:
		IdleState();
		break;
	case Chase:
		ChaseState();
		break;
	case Attack:
		AttackState();
		break;
	case Death:
		DeathState();
		break;
	default:
		break;
	}


	GameObject::Update(dt);
}

void Enemy::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
}

void Enemy::IdleState()
{
	//std::cout << "Idling" << std::endl;
}

void Enemy::ChaseState()
{
	// Get direction
	LLGP::Vector2f direction = _playerRef->GetTransform()->GetPosition() - GetTransform()->GetPosition();
	
	// Chase towawrds the player
	GetRigidbody()->AddForce(direction.Normalised() * mMaxSpeed);
}

void Enemy::AttackState()
{
	//std::cout << "Attacking" << std::endl;
	
}

void Enemy::DeathState()
{
}

void Enemy::UpdateStates()
{
	float  distanceToPlayer = (_playerRef->GetTransform()->GetPosition() - GetTransform()->GetPosition()).GetMagnitude();

	if (distanceToPlayer <= AttackDistance)
	{
		ChangeCurrentState(States::Attack);
	}
	else
	{
		ChangeCurrentState(States::Chase);
	}
}

void Enemy::OnCollision(GameObject& other)
{
	if (Player* player = dynamic_cast<Player*>(&other))
	{
		std::cout << "Player collided with enemy" << std::endl;
	}
}




