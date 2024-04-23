#pragma once
#include "Event.h"
class GameObject;

class HealthComponent
{
public:
	HealthComponent(GameObject* Owner);
	~HealthComponent();
	
	void UpdateHealth();

	void TakeDamage(const GameObject* Source, float Amount);
	
	void Kill();

	void SetMaxHealth(float Amount) { mMaxHealth = Amount; }

	float GetCurrentHealth() const { return mCurrentHealth; }


	

	LLGP::Event<float> OnHealthUpdated;
	LLGP::Event<bool> OnDied;

private:
	float mCurrentHealth;
	float mMaxHealth = 100.0f;
	float mMinimumHealth = 0.0f;

	GameObject* mOwner;

};

