#include "Texture2D.h"

Texture2D::Texture2D(sf::Texture* texture)
{
	mSprite = new sf::Sprite(*texture);
	//mSprite = new sf::Sprite();
	//SetTexture(*texture);
}



Texture2D::~Texture2D()
{
}

void Texture2D::Draw(sf::RenderWindow& window)
{
	window.draw(*mSprite);
	
}
