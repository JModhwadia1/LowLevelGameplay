#include "Entity.h"

Entity::Entity(sf::Texture& texture)
{
	_texture = new Texture2D(texture);
	_transform = new Transform(LLGP::Vector2f(0, 0), LLGP::Vector2f(1, 1));
	_rigidbody = new Rigidbody(_transform);

}

Entity::~Entity()
{
}

void Entity::Update(float dt)
{
	_rigidbody->Update(dt);
	//mSprite.setPosition(_transform->GetPosition());
	_texture->GetSprite()->setPosition(_transform->GetPosition());
}

void Entity::Draw(sf::RenderWindow& window)
{
	_texture->Draw(window);
}
