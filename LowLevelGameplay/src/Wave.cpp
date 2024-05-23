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
	/*for (int i = 0; i < mGruntsInWave.size(); i++)
	{
		mGruntsInWave[i]->SetActive(false);
	}*/

	/*for (int i = 0; i < mFamilyManInWave.size(); i++)
	{
		mFamilyManInWave[i]->SetActive(false);
	}*/
}
void Wave::ReduceGruntCount(bool die, int pointsTogive) {
	
}
void Wave::SpawnEnemies(float dt)
{

	if (shouldStartSpawningEnemies) {
		spawnDelay -= dt;

		for (int i = 0; i <= _numberOfGruntsToSpawn; i++)
		{
			if (spawnDelay <= 0.0f && _numberOfGruntsInWave <= _numberOfGruntsToSpawn)
			{
				LLGP::Vector2f spawnPos = GameWorld::GetRandomPosInArena();
				Grunts* grunt = ObjectPool::GetPooledObjectAsType<Grunts>("Grunts");
				grunt->GetTransform()->SetPosition(spawnPos);
				grunt->OnEnemyDied.AddListener(this, std::bind(&Wave::HandleGruntsDied, this, std::placeholders::_1, std::placeholders::_2));
				mGruntsInWave.push_back(grunt);
				_numberOfGruntsInWave++;
				std::cout << _numberOfGruntsInWave << std::endl;
				spawnDelay = 0.2f;
			}
			else if (_numberOfGruntsInWave == _numberOfGruntsToSpawn) {
				OnAllGruntsSpawned.Invoke(this);
				std::cout << "All grunts spawned" << std::endl;
			}

		}
	}
}

void Wave::HandleGruntsDied(bool died, int points) 
{
	std::cout << "Grunt died: Wave.cpp" << std::endl;
	_numberOfGruntsDied++;
	std::cout << "Number of grunts died: " << _numberOfGruntsDied << std::endl;
	if (_numberOfGruntsDied == _numberOfGruntsToSpawn) {
		OnWaveComplete.Invoke(this);
		std::cout << "wave completed" << std::endl;
	}
}
