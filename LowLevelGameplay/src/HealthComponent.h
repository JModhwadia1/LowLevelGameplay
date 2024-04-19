#pragma once
#include "Event.h"
class HealthComponent
{
public:
	HealthComponent();
	~HealthComponent();
	
	void UpdateHealth();

	void TakeDamage(float Amount);
	
	void Kill();

	void SetMaxHealth(float Amount) { mMaxHealth = Amount; }

	float GetCurrentHealth() const { return mCurrentHealth; }


	LLGP::Event<float> OnHealthUpdated;
private:
	float mCurrentHealth;
	float mMaxHealth = 100.0f;
	float mMinimumHealth = 0.0f;

};

