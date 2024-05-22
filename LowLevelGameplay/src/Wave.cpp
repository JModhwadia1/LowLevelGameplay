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
}

Wave::~Wave()
{

}

void Wave::ClearWave()
{
	for (int i = 0; i < mGruntsInWave.size(); i++)
	{
		mGruntsInWave[i]->SetActive(false);
	}

	for (int i = 0; i < mFamilyManInWave.size(); i++)
	{
		mFamilyManInWave[i]->SetActive(false);
	}
}
void Wave::ReduceGruntCount(bool die, int pointsTogive) {
	
}
void Wave::SpawnEnemies(float dt)
{
	spawnDelay -= dt;

	for (int i = 0; i <= _numberOfGruntsToSpawn; i++)
	{
		if (spawnDelay <= 0.0f && _numberOfGruntsInWave <= _numberOfGruntsToSpawn)
		{
			LLGP::Vector2f spawnPos = GameWorld::GetRandomPosInArena();
			Grunts* grunt = ObjectPool::GetPooledObjectAsType<Grunts>("Grunts");
			grunt->GetTransform()->SetPosition(spawnPos);
			
			mGruntsInWave.push_back(grunt);
			_numberOfGruntsInWave++;
			spawnDelay = 1.0f;
		}
		else if (_numberOfGruntsInWave <= _numberOfGruntsToSpawn) {
			OnAllGruntsSpawned.Invoke();
		}
		
	}
	//for (int i = 0; i <= _numberOfHulksToSpawn; i++)
	//{
	//	if (spawnDelay <= 0.0f && _numberOfHulksInWave <= _numberOfHulksToSpawn)
	//	{
	//		LLGP::Vector2f spawnPos = GameWorld::GetRandomPosInArena();
	//		Hulks* hulk =/* GameWorld::SpawnGameobject<Hulks>();*/ObjectPool::GetPooledObjectAsType<Hulks>("Hulks");
	//		hulk->GetTransform()->SetPosition(spawnPos);

	//		//	grunt->SetActive(true);
	//		mEnemiesInWave.push_back(hulk);
	//		_numberOfHulksInWave++;
	//		spawnDelay = 0.5f;
	//	}
	//}




}
