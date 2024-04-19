#include "HealthComponent.h"

HealthComponent::HealthComponent()
{
	mCurrentHealth = mMaxHealth;
}

HealthComponent::~HealthComponent()
{
	
}

void HealthComponent::UpdateHealth()
{
	
}

void HealthComponent::TakeDamage(float Amount)
{
	if (mCurrentHealth - Amount <= mMinimumHealth) {
		Kill();
		OnHealthUpdated(0);
	}
	else
	{
		mCurrentHealth -= Amount;
		OnHealthUpdated(mCurrentHealth);
		UpdateHealth();
	}

}

void HealthComponent::Kill()
{

}



