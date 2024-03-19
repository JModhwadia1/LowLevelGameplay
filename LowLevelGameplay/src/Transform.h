#pragma once
#include "Vector2.h"
#include "SFML/Graphics.hpp"

class Transform
{
public:
	Transform(LLGP::Vector2f pos, LLGP::Vector2f scale);
	~Transform();



	// Position
	void SetPosition(LLGP::Vector2f& pos) { mPosition = pos; }
	 LLGP::Vector2f GetPosition() { return mPosition; }
	
	void SetScale(LLGP::Vector2f& scale) { mScale = scale; }
	 LLGP::Vector2f GetScale() { return mScale; }

	void SetRotation(float angle, sf::Sprite sprite) { sprite.setRotation(LLGP::RadiansToDegrees(angle)); }
	float GetRotation(sf::Sprite sprite) { return LLGP::DegreesToRadians(sprite.getRotation()); }


private:
	LLGP::Vector2f mPosition = LLGP::Vector2f(0, 0);
	LLGP::Vector2f mScale = LLGP::Vector2f(1, 1);

};

