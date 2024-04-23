#include "HealthComponent.h"
#include "GameObject.h"

HealthComponent::HealthComponent(GameObject* Owner) /*: mOwner(Owner)*/
{
	mCurrentHealth = mMaxHealth;
	mOwner = Owner;
	//mOwner->OnDamageTaken += std::bind(&HealthComponent::TakeDamage, this, std::placeholders::_1);
	//mOwner->OnDamageTaken += std::bind(&HealthComponent::TakeDamage, this, std::placeholders::_1);
	
	
}

HealthComponent::~HealthComponent()
{
	
}

void HealthComponent::UpdateHealth()
{
	
}


void HealthComponent::TakeDamage(const GameObject* Source, float Amount)
{
	if (mCurrentHealth - Amount <= mMinimumHealth) {
		Kill();
		OnHealthUpdated(0.0f);
		OnDied(true);
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



