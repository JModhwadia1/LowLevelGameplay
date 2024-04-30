#pragma once
#include "Family.h"

class FamilyMan : public Family
{
public:
	FamilyMan(GameWorld* world, sf::Texture* texture);
	~FamilyMan();
	
	void IdleState() override;
	void WanderState(float dt) override;
	void DeathState() override;
	void Draw(sf::RenderWindow* window)override;
	void Update(float dt) override;
	void UpdateStates() override;

private:
	float m_NewPointGenTime = 2.0f;
	LLGP::Vector2f randomPoint;

};

