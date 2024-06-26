#include "GameObject.h"
#include "Event.h"
#include "Constants.h"
#include <GameWorld.h>

void GameObject::Init(sf::Texture* texture)
{
	_texture = std::make_unique<Texture2D>(texture);
	_transform = std::make_unique<Transform>(LLGP::Vector2f(0, 0), LLGP::Vector2f(1, 1));
	_rigidbody = std::make_unique<Rigidbody>(_transform.get(), _texture->GetSprite());
}

GameObject::~GameObject()
{

}



void GameObject::Update(float dt)
{
	//if (!m_Active) return;
}

void GameObject::Draw(sf::RenderWindow* window)
{
//	if (!m_Active) { return; }
	_texture->Draw(window);
}

void GameObject::ApplyDamage(GameObject* source, float damage)
{
	OnDamageTaken(source, damage);
}

