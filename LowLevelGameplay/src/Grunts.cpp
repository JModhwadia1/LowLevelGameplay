#include "Grunts.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Player.h"
#include "GameWorld.h"
#include "HealthComponent.h"
#include "Bullet.h"
Grunts::Grunts() : Enemy(GameWorld::GetResources().mGruntsTex)
{
	/*SetActive(true);*/
	SetActive(false);
	mMaxSpeed = 10.0f;
	GetRigidbody()->SetMaxSpeed(mMaxSpeed);
	GetTexture2D()->GetSprite()->setScale(5, 5);
	_healthComponent = new HealthComponent(this);
	_healthComponent->SetMaxHealth(10.0f);
	_healthComponent->OnDied.AddListener(this, std::bind(&Grunts::HandleOnDied, this, std::placeholders::_1));
	_boxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(GetTexture2D()->GetSprite()->getGlobalBounds().getSize().x, GetTexture2D()->GetSprite()->getGlobalBounds().getSize().y));
	_sphereCollider = new SphereCollider(GetTransform(), 30.0f);
	SetCollider(_sphereCollider);

	SetName("Grunts");
	_playerRef = GameWorld::GetPlayer();
	_playerRef->OnPlayerDied.AddListener(this, std::bind(&Grunts::HandlePlayerDied, this, std::placeholders::_1));
}

Grunts::~Grunts()
{
	delete _healthComponent;
	delete _boxCollider;
	delete _sphereCollider;
	_sphereCollider = nullptr;
	_boxCollider = nullptr;
	_healthComponent = nullptr;
	_playerRef->OnPlayerDied.RemoveListener(this, std::bind(&Grunts::HandlePlayerDied, this, std::placeholders::_1));
	_playerRef = nullptr;
}


void Grunts::Start()
{

}

void Grunts::Update(float dt)
{
	if (!GetIsActive()) return;
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
	if (!GetIsActive()) return;
	GetRigidbody()->AddForce(direction.Normalised() * mMaxSpeed);
	GetRigidbody()->Update(fixedUpdate);
}

void Grunts::Draw(sf::RenderWindow* window)
{
	if (!GetIsActive()) return;
	GameObject::Draw(window);
	window->draw(shape);
}

void Grunts::IdleState()
{
	if (!GetIsActive()) return;
	//std::cout << "Idling" << std::endl;
}

void Grunts::ChaseState()
{
	if (!GetIsActive()) return;

	// Get direction
	if (_playerRef == nullptr) return;
	direction = _playerRef->GetTransform()->GetPosition() - GetTransform()->GetPosition();

	
}

void Grunts::AttackState()
{
	if (!GetIsActive()) return;
	//std::cout << "Attacking" << std::endl;

}

void Grunts::DeathState()
{
	if (!GetIsActive()) return;
}

void Grunts::UpdateStates()
{
	//if (_playerRef == nullptr) return;
	if (!GetIsActive()) return;
	if (_playerRef == nullptr)return;
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
		//SetActive(false);
		SetActive(false);
		
		
		
	}
}

void Grunts::HandlePlayerDied(bool die)
{
	if (die) {
		_playerRef = nullptr;
	}
}

void Grunts::OnCollision(GameObject& other)
{
	if (Player* player = dynamic_cast<Player*>(&other))
	{
		//std::cout << "collided with player" << std::endl;;
	}
	
}

