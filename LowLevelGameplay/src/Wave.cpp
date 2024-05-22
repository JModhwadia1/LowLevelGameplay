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
	_numberOfGruntsToSpawn = numberOfGrunts;
	_numberOfHulksToSpawn = numberOfHulks;
	_numberOfFamilyMenToSpawn = numberOfFamilyMen;
	_numberofBrainsToSpawn = numberofBrains;

	//for (int i = 0; i <= numberOfGrunts; i++)
	//{
	//	srand(time(NULL));
	//	LLGP::Vector2f spawnPos = GameWorld::GetRandomPosInArena();
	//	Grunts* grunt = ObjectPool::GetPooledObjectAsType<Grunts>("Grunts");
	//	grunt->GetTransform()->SetPosition(spawnPos);
	//	GameWorld::AddToGameobjects(grunt);
	//	grunt->SetActive(true);
	//	mEnemiesInWave.push_back(grunt);
	//}
	/*for (int i = 0; i <= numberOfHulks; i++)
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
	}*/


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

void Wave::SpawnEnemies(float dt)
{
	spawnDelay -= dt;

	for (int i = 0; i <= _numberOfGruntsToSpawn; i++)
	{
		if (spawnDelay <= 0.0f && _numberOfGruntsInWave <= _numberOfGruntsToSpawn) 
		{
				LLGP::Vector2f spawnPos = GameWorld::GetRandomPosInArena();
				Grunts* grunt = /*GameWorld::SpawnGameobject<Grunts>();*/ObjectPool::GetPooledObjectAsType<Grunts>("Grunts");
				grunt->GetTransform()->SetPosition(spawnPos);
			//	grunt->SetActive(true);
					//	grunt->SetActive(true);
				mEnemiesInWave.push_back(grunt);
				_numberOfGruntsInWave++;
				spawnDelay = 0.5f;
		}	
    }
	for (int i = 0; i <= _numberOfHulksToSpawn; i++)
	{
		if (spawnDelay <= 0.0f && _numberOfHulksInWave <= _numberOfHulksToSpawn)
		{
			LLGP::Vector2f spawnPos = GameWorld::GetRandomPosInArena();
			Hulks* hulk=/* GameWorld::SpawnGameobject<Hulks>();*/ObjectPool::GetPooledObjectAsType<Hulks>("Hulks");
			hulk ->GetTransform()->SetPosition(spawnPos);

			//	grunt->SetActive(true);
			mEnemiesInWave.push_back(hulk);
			_numberOfHulksInWave++;
			spawnDelay = 0.5f;
		}
	}


	
		
}
