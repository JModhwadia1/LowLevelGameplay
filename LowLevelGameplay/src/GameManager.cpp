#include "GameManager.h"
#include "Wave.h"
#include "GameWorld.h"
#include "Grunts.h"
#include "Player.h"

GameManager::GameManager() 
{
	wave1 = new Wave(100, 10, 10, 10);
	wave1->OnAllGruntsSpawned.AddListener(this, std::bind(&GameManager::BindToGruntsDiedEvent, this));
	
	GameWorld::GetPlayer()->OnPlayerDied.AddListener(this, std::bind(&GameManager::HandlePlayerDied, this, std::placeholders::_1));
	
}
GameManager::~GameManager() 
{
	for (int i = 0; i < wave1->GetGruntsInWave().size(); i++)
	{
		wave1->GetGruntsInWave()[i]->OnEnemyDied.RemoveListener(this, std::bind(&GameManager::HandleEnemyDied, this, std::placeholders::_1, std::placeholders::_2));
	}
	delete wave1;
	wave1 = nullptr;


}

void GameManager::Init()
{

	


	


	
}
void GameManager::BindToGruntsDiedEvent() {
	for (int i = 0; i < wave1->GetGruntsInWave().size(); i++)
	{
		wave1->GetGruntsInWave()[i]->OnEnemyDied.AddListener(this, std::bind(&GameManager::HandleEnemyDied, this, std::placeholders::_1, std::placeholders::_2));

	}

}

void GameManager::Update(float dt) {
	wave1->SpawnEnemies(dt);
	
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

