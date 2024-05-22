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
