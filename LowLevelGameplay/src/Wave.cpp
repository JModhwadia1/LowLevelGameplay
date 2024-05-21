#include "Wave.h"
#include "ObjectPool.h"

#include "Enemy.h"
#include "Grunts.h"
#include "FamilyMan.h"
#include "Hulks.h"
#include "Brains.h"
#include "GameWorld.h"
Wave::Wave(int numberOfGrunts, int numberOfHulks, int numberOfFamilyMen, int numberofBrains)
{
	for (int i = 0; i <= numberOfGrunts; i++)
	{
		Grunts* grunt = ObjectPool::GetPooledObjectAsType<Grunts>("Grunts");
		grunt->GetTransform()->SetPosition(GameWorld::GetRandomPosInArena());

		mEnemiesInWave.push_back(grunt);
	}
	for (int i = 0; i <= numberOfHulks; i++)
	{
		Hulks* hulk = ObjectPool::GetPooledObjectAsType<Hulks>("Hulks");
		hulk->GetTransform()->SetPosition(GameWorld::GetRandomPosInArena());
		mEnemiesInWave.push_back(hulk);
	}
	for (int i = 0; i < numberOfFamilyMen; i++)
	{
		FamilyMan* family = ObjectPool::GetPooledObjectAsType<FamilyMan>("FamilyMan");
		family->GetTransform()->SetPosition(GameWorld::GetRandomPosInArena());
		mFamilyManInWave.push_back(family);
	}
	for (int i = 0; i < numberofBrains; i++)
	{
		Brains* brain = ObjectPool::GetPooledObjectAsType<Brains>("Brains");
		brain->GetTransform()->SetPosition(GameWorld::GetRandomPosInArena());
		mEnemiesInWave.push_back(brain);
	}


}

Wave::~Wave()
{
	
}

void Wave::ClearWave()
{
	for (int i = 0; i < mEnemiesInWave.size(); i++)
	{
		mEnemiesInWave[i]->SetActive(false);
	}

	for (int i = 0; i < mFamilyManInWave.size(); i++)
	{
		mFamilyManInWave[i]->SetActive(false);
	}
}
