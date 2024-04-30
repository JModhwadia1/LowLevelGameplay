#include "Texture2D.h"

Texture2D::Texture2D(sf::Texture* texture)
{
	mSprite = new sf::Sprite(*texture);
}



Texture2D::~Texture2D()
{
	mSprite = nullptr;
}

void Texture2D::Draw(sf::RenderWindow* window)
{
	window->draw(*mSprite);
}
