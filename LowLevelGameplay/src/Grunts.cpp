#include "Grunts.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Player.h"
#include "GameWorld.h"
#include "HealthComponent.h"
Grunts::Grunts() 
{
	SetActive(false);
	pointsToGive = 100.0f;
	Init(GameWorld::GetResources().mGruntsTex);
	mMaxSpeed = 100.0f;
	GetTransform()->SetPosition(GameWorld::GetRandomPosInArena());
	GetRigidbody()->SetMaxSpeed(mMaxSpeed);
	SetName("Grunts");
	GetTexture2D()->GetSprite()->setScale(4, 4);
	_healthComponent = new HealthComponent(this);
	_healthComponent->SetMaxHealth(10.0f);
	_healthComponent->OnDied.AddListener(this, std::bind(&Grunts::HandleOnDied, this, std::placeholders::_1));
	_boxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(GetTexture2D()->GetSprite()->getScale().x * 5, GetTexture2D()->GetSprite()->getScale().y * 11));
	_sphereCollider = new SphereCollider(GetTransform(), 30.0f);
	SetCollider(_boxCollider);
	_playerRef = GameWorld::GetPlayer();
	_playerRef->OnPlayerDied.AddListener(this, std::bind(&Grunts::HandlePlayerDied, this, std::placeholders::_1));

}

Grunts::~Grunts()
{
	delete _healthComponent;
	delete _boxCollider;
	delete _sphereCollider;
	_playerRef->OnPlayerDied.RemoveListener(this, std::bind(&Grunts::HandlePlayerDied, this, std::placeholders::_1));
	_playerRef = nullptr;
}




void Grunts::Update(float dt)
{
	shape.setSize(_boxCollider->GetHalfExtents());
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(3.0f);
	shape.setOutlineColor(sf::Color::Red);
	shape.setPosition(GetTransform()->GetPosition());

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


	
}

void Grunts::FixedUpdate(float fixedUpdate)
{

	GetRigidbody()->AddForce(direction.Normalised() * mMaxSpeed);
	GetRigidbody()->Update(fixedUpdate);
}

void Grunts::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
	window->draw(shape);
}

void Grunts::IdleState()
{
	//std::cout << "Idling" << std::endl;
}

void Grunts::ChaseState()
{

	// Get direction
	if (_playerRef == nullptr) return;
	direction = _playerRef->GetTransform()->GetPosition() - GetTransform()->GetPosition();

	
}

void Grunts::AttackState()
{
	//std::cout << "Attacking" << std::endl;

}

void Grunts::DeathState()
{
}

void Grunts::UpdateStates()
{
	//if (_playerRef == nullptr) return;

	if (_playerRef == nullptr) return;
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

void Grunts::HandleOnDied(bool die)
{
	if (die) {
	
		OnEnemyDied.Invoke(true, pointsToGive);
		SetActive(false);
		
	}
}

void Grunts::HandlePlayerDied(bool die)
{
	if (GameWorld::GetPlayer() == nullptr) {
		_playerRef = nullptr;
	}
}

void Grunts::OnCollision(GameObject& other)
{

	if (_playerRef != nullptr && _playerRef == &other) 
	{
		_playerRef->ApplyDamage(this, 1000.0f);
	}
}

