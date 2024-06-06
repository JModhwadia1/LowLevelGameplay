#include "GameManager.h"
#include "Wave.h"
#include "GameWorld.h"
#include "Grunts.h"
#include "Player.h"

GameManager::GameManager() 
{
	/*wave1 = new Wave(100, 10, 10, 10);
	wave1->OnAllGruntsSpawned.AddListener(this, std::bind(&GameManager::BindToGruntsDiedEvent, this));*/
	
	GameWorld::GetPlayer()->OnPlayerDied.AddListener(this, std::bind(&GameManager::HandlePlayerDied, this, std::placeholders::_1));

	//waves[0] = new Wave(10, 10, 10, 10);
	//waves[0]->OnAllGruntsSpawned.AddListener(this, std::bind(&GameManager::BindToGruntsDiedEvent, this,std::placeholders::_1));
	//waves[0]->OnWaveComplete.AddListener(this, std::bind(&GameManager::ClearWave, this, std::placeholders::_1));
	//waves[0]->shouldStartSpawningEnemies = true;

	Wave* wave = new Wave(10, 10, 10, 10);
	wave->OnAllGruntsSpawned.AddListener(this, std::bind(&GameManager::BindToGruntsDiedEvent, this, std::placeholders::_1));
	wave->OnWaveComplete.AddListener(this, std::bind(&GameManager::ClearWave, this, std::placeholders::_1));
	wave->shouldStartSpawningEnemies = true;


	Wave* wave2 = new Wave(10, 10, 10, 10);
	wave2->OnAllGruntsSpawned.AddListener(this, std::bind(&GameManager::BindToGruntsDiedEvent, this, std::placeholders::_1));
	wave2->OnWaveComplete.AddListener(this, std::bind(&GameManager::ClearWave, this, std::placeholders::_1));
	wave2->shouldStartSpawningEnemies = false;

	waves.push_back(wave);
	waves.push_back(wave2);
}
GameManager::~GameManager() 
{
	for (int i = 0; i < waves.size(); i++)
	{
		waves[i]->GetGruntsInWave()[i]->OnEnemyDied.RemoveListener(this, std::bind(&GameManager::HandleEnemyDied, this, std::placeholders::_1, std::placeholders::_2));
	}



}

void GameManager::Init()
{

	


	


	
}
void GameManager::BindToGruntsDiedEvent(Wave* wave) {
	for (int i = 0; i < wave->GetGruntsInWave().size(); i++)
	{
		wave->GetGruntsInWave()[i]->OnEnemyDied.AddListener(this, std::bind(&GameManager::HandleEnemyDied, this, std::placeholders::_1, std::placeholders::_2));

	}

}

void GameManager::Update(float dt)
{
	for (int i = 0; i < waves.size(); i++)
	{
		if (waves[i]->shouldStartSpawningEnemies) {
			waves[i]->SpawnEnemies(dt);
		}
	}
	
}

void GameManager::HandleEnemyDied(bool Die, int PointsToGive) 
{
	mPlayerPoints += PointsToGive;
	std::cout << mPlayerPoints << std::endl;
	OnPlayerPointUpdated.Invoke(mPlayerPoints);
}

void GameManager::HandlePlayerDied(bool die) 
{
	if (die && mPlayerLives != 0) 
	{
		mPlayerLives -= 1;;
		OnPlayerLivesUpdated.Invoke(mPlayerLives + 1);
		GameWorld::GetPlayer()->GetTransform()->SetPosition(LLGP::Vector2f(960.0f, 540.0f));
		GameWorld::GetPlayer()->SetInvinvible(true);
	}
	else {
		GameWorld::RemovePlayer();
		OnPlayerLivesUpdated.Invoke(0);
	}
}

void GameManager::ClearWave(Wave* wave)
{
	// sets all the enemies to inactive
	wave->ClearWave();
	wave->shouldStartSpawningEnemies = false;
	wavesCompleted++;

	// check to see if we have not reached the end of waves
	if (wavesCompleted < waves.size()) {
	
		// increment wave
		waves[wavesCompleted]->shouldStartSpawningEnemies = true;
	}
}

