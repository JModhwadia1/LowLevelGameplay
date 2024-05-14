#pragma once
#include "Transform.h"
#include "Texture2D.h"
#include "Rigidbody.h"
#include "Object.h"
#include "Event.h"


class Collider;
class GameWorld;
class GameObject : public Object
{
public:
	GameObject() = default;
	GameObject(sf::Texture* texture);
	~GameObject();

	virtual void Start();
	virtual void Update(float dt);
	virtual void FixedUpdate(float fixedUpdate) {};
	virtual void Draw(sf::RenderWindow* window);
	Rigidbody* GetRigidbody() { return _rigidbody; }
	Texture2D* GetTexture2D() { return _texture; }
	Transform* GetTransform() { return _transform; }

	inline void SetName(std::string newName) { m_Name = newName; }
	inline std::string GetName() { return m_Name; }
	void SetActive(bool newActive) { m_Active = newActive; }
	bool GetIsActive() { return m_Active; }
	inline void SetTag(std::string newTag) { m_Tag = newTag; }
	
	inline bool CompareTag(std::string comp) { return m_Tag == comp; }
	void SetCollider(Collider* collider) { _collider = collider; }
	Collider* GetCollider() { return _collider; }
	
	void ApplyDamage( GameObject* source, float damage);

	template<class T> requires isComponent<T> T* GetComponent();
	template<class T> requires isComponent<T> T* AddComponent();
	template<class T> requires isComponent<T>  bool RemoveComponent(T* comp);

	bool IsCollideable() const { return _collider != nullptr; }

	virtual void OnCollision(GameObject& other) {}


	LLGP::Event<GameObject*, float> OnDamageTaken;

protected:
	virtual bool ColllidesWith(const GameObject& other) const { return false; }


private:
	std::string m_Name;
	std::string m_Tag;
	bool m_Active;
	Collider* _collider = nullptr;

	Texture2D* _texture;
	Transform* _transform;
	Rigidbody* _rigidbody;
	std::vector <std::unique_ptr<Component>> m_Components;
};

