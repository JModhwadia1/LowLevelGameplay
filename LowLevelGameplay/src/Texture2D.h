#pragma once
#include <SFML/Graphics.hpp>

class Texture2D
{
public:

	Texture2D(sf::Texture& texture);
	~Texture2D();
	void Draw(sf::RenderWindow& window);
	void SetTexture(sf::Texture& texture) { mSprite->setTexture(texture); }
	sf::Texture GetTexture() { return &mSprite->getTexture(); }
private:
	sf::Sprite* mSprite;
};

