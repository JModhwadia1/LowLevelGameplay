#include "Brains.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Player.h"
#include "GameWorld.h"
#include "HealthComponent.h"
#include "Bullet.h"
#include "ObjectPool.h"

Brains::Brains() 
{
	Init(GameWorld::GetResources().mBrainsTex);
	//mShootCooldown = 0.0f;
	mMaxSpeed = 100.0f;
	AttackDistance = 200.0f;
	GetRigidbody()->SetMaxSpeed(mMaxSpeed);
	GetTexture2D()->GetSprite()->setScale(5, 5);
	_healthComponent = new HealthComponent(this);
	_healthComponent->SetMaxHealth(10.0f);
	_healthComponent->OnDied.AddListener(this, std::bind(&Brains::HandleOnDied, this, std::placeholders::_1));
	_boxCollider = new BoxCollider(GetTransform(), LLGP::Vector2f(GetTexture2D()->GetSprite()->getGlobalBounds().getSize().x, GetTexture2D()->GetSprite()->getGlobalBounds().getSize().y));
	_sphereCollider = new SphereCollider(GetTransform(), 30.0f);
	SetCollider(_boxCollider);
	_playerRef = GameWorld::GetPlayer();
	_playerRef->OnPlayerDied.AddListener(this, std::bind(&Brains::HandlePlayerDied, this, std::placeholders::_1));

	std::cout << "brains constructed" << std::endl;
}

Brains::~Brains()
{
	delete _healthComponent;
	delete _boxCollider;
	delete _sphereCollider;
	_playerRef->OnPlayerDied.RemoveListener(this, std::bind(&Brains::HandlePlayerDied, this, std::placeholders::_1));
	_playerRef = nullptr;
}

void Brains::Start()
{
}

void Brains::Update(float dt)
{
	shape.setSize(_boxCollider->GetHalfExtents());
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(3.0f);
	shape.setOutlineColor(sf::Color::Red);
	shape.setPosition(GetTransform()->GetPosition());

	UpdateStates();

	if (_currentState == States::Attack) {
		mShootCooldown -= dt;
		if (mShootCooldown <= 0) {
			mShootCooldown = mShootDelay;
			BulletLaunchParams params;
			params.mOwner = this;
			params.mStartPos = GetTransform()->GetPosition();
			params.mDirection = direction.Normalised();
			params.mDamage = 10.0f;

			if (Bullet* bullet = ObjectPool::GetPooledObjectAsType<Bullet>("Bullet")) 
			{
				bullet->Launch(&params);
				std::cout << "Bullet spawned" << std::endl;
			}
		}
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

void Brains::FixedUpdate(float fixedUpdate)
{
	GetRigidbody()->AddForce(direction.Normalised() * mMaxSpeed);
	GetRigidbody()->Update(fixedUpdate);
}

void Brains::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
	window->draw(shape);
}

void Brains::IdleState()
{
}

void Brains::ChaseState()
{
	// Get direction
	if (_playerRef == nullptr) return;
	direction = _playerRef->GetTransform()->GetPosition() - GetTransform()->GetPosition();
	

}

void Brains::AttackState()
{
	
}

void Brains::DeathState()
{
}

void Brains::UpdateStates()
{
	if (_playerRef == nullptr) return;
	float distanceToPlayer = (_playerRef->GetTransform()->GetPosition() - GetTransform()->GetPosition()).GetMagnitude();

	if (distanceToPlayer <= AttackDistance) 
	{	
		ChangeCurrentState(States::Attack);
	}
	else
	{
		ChangeCurrentState(States::Chase);
	}
}
void Brains::HandleOnDied(bool die)
{
	if (die) 
	{
		std::cout << "Brains has died" << std::endl;
	}
}
void Brains::HandlePlayerDied(bool die)
{
	if (die) 
	{
		_playerRef = nullptr;
	}
}

void Brains::OnCollision(GameObject& other)
{
	if (Player* player = dynamic_cast<Player*>(&other))
	{
		std::cout << "Collided with player" << std::endl;
	}
}
