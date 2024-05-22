#include "Hulks.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Player.h"
#include "GameWorld.h"
#include "HealthComponent.h"
Hulks::Hulks() 
{
	Init(GameWorld::GetResources().mHulksTex);
	mMaxSpeed = 20.0f;
	GetRigidbody()->SetMaxSpeed(mMaxSpeed);
	GetTexture2D()->GetSprite()->setScale(5, 5);
	_healthComponent = new  HealthComponent(this);
	_healthComponent->SetMaxHealth(10.0f);
	_healthComponent->OnDied.AddListener(this, std::bind(&Hulks::HandleOnDied, this, std::placeholders::_1));
	_boxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(GetTexture2D()->GetSprite()->getGlobalBounds().getSize().x, GetTexture2D()->GetSprite()->getGlobalBounds().getSize().y));
	_sphereCollider = new SphereCollider(GetTransform(), 30.0f);
	SetCollider(_boxCollider);
	randomPoint = GameWorld::GetRandomPosInArena();
	ChangeCurrentState(States::Chase);

}

Hulks::~Hulks()
{
	delete _healthComponent;
	delete _boxCollider;
	delete _sphereCollider;
	_playerRef->OnPlayerDied.RemoveListener(this, std::bind(&Hulks::HandlePlayerDied, this, std::placeholders::_1));
	_playerRef = nullptr;
}

void Hulks::Start()
{
}

void Hulks::Update(float dt)
{
	shape.setSize(_boxCollider->GetHalfExtents());
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(3.0f);
	shape.setOutlineColor(sf::Color::Red);
	shape.setPosition(GetTransform()->GetPosition());
	UpdateStates();


	m_NewPointGenTime -= dt;
	if (m_NewPointGenTime <= 0.0f) {
		m_NewPointGenTime = 2.0f;
		randomPoint = GameWorld::GetRandomPosInArena();

	}

	if (GetTransform()->GetPosition() == randomPoint && m_NewPointGenTime <= 0.0f) {
		randomPoint = GameWorld::GetRandomPosInArena();
	}

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

void Hulks::FixedUpdate(float fixedUpdate)
{
	GetRigidbody()->AddForce(direction.Normalised() * mMaxSpeed);
	GetRigidbody()->Update(fixedUpdate);
}

void Hulks::Draw(sf::RenderWindow* window)
{

	GameObject::Draw(window);
	window->draw(shape);
}

void Hulks::IdleState()
{
}

void Hulks::ChaseState()
{
	direction = randomPoint - GetTransform()->GetPosition();
}

void Hulks::AttackState()
{
}

void Hulks::DeathState()
{
}

void Hulks::UpdateStates()
{

}

void Hulks::HandleOnDied(bool die)
{
}

void Hulks::HandlePlayerDied(bool die)
{
}

void Hulks::OnCollision(GameObject& other)
{
}
