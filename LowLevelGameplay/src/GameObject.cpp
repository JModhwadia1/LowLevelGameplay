#include "GameObject.h"
#include "Event.h"

#include <GameWorld.h>

GameObject::GameObject(sf::Texture* texture)
{
	_texture = new Texture2D(texture);
	_transform = new Transform(LLGP::Vector2f(0, 0), LLGP::Vector2f(1, 1));
	_rigidbody = new Rigidbody(_transform);
}

GameObject::~GameObject()
{
	delete(_rigidbody);
	delete(_transform);
	delete(_collider);

}

void GameObject::Start()
{
}

void GameObject::Update(float dt)
{
	_rigidbody->Update(dt);
	_texture->GetSprite()->setPosition(_transform->GetPosition());
}

void GameObject::Draw(sf::RenderWindow* window)
{
	_texture->Draw(window);
}

void GameObject::ApplyDamage(GameObject* source, float damage)
{
	OnDamageTaken(source, damage);
}

template <class T> requires isComponent<T>
T* GameObject::GetComponent()
{
	T* returnComp = nullptr;

	for (int i = 0; i < m_Components.size(); i++)
	{
		returnComp = static_cast<T*>(m_Components[i].get());
		if (returnComp != nullptr)
		{
			break;
		}
	}
	return returnComp;
}
template<class T> requires isComponent<T>
T* GameObject::AddComponent()
{
	std::unique_ptr<Component> newComp = std::make_unique<T>(this);
	m_Components.push_back(std::move(newComp));
	return static_cast<T*>(m_Components[m_Components.size()].get());
}
template<class T> requires isComponent<T>
bool GameObject::RemoveComponent(T* comp)
{
	if (!std::find(m_Components.begin, m_Components.end, comp))
	{
		return false;
	}
	else 
	{
		m_Components.erase(comp);
		return true;
	}	
}
