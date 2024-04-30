#pragma once
#include <SFML/Graphics.hpp>
//#include "Player.h"
#include "GameObject.h"
//#include "Enemy.h"
#include "Event.h"
#include "ObjectPool.h"
#include <iostream>

class FamilyMan;
class Player;
class Enemy;
//class Enemy;




class GameWorld
{
public:

	struct Resources {
		sf::Texture* mPlayerTex;
		sf::Texture* mEnemyTex;
		sf::Texture* mBulletTex;
		sf::Texture* mMenTex;
		sf::Texture* mWomenTex;
		sf::Texture* mBoyTex;
		
		// Enemies Textures
		sf::Texture* mGruntsTex;
		sf::Texture* mHulksTex;
		sf::Texture* mBrainsTex;
		sf::Texture* mSpheroidsTex;
		sf::Texture* mEnforcersTex;
		sf::Texture* mTanksTex;
	};


public:
	 GameWorld() = default;
	 GameWorld(sf::RenderWindow* window);
	 ~GameWorld();
	const float arenaSize = 900;

	// Positions of each side of the area (Note: does not affect arena visually)
	float m_ArenaLeftPos = 500.0f;
	float m_ArenaRightPos = 1430.0f;
	float m_ArenaTopPos = 50.0f;
	float m_ArenaBottomPos = 950.0f;
	void Init();
	void LoadTextures();
	void Update(float DeltaTime);
	void Render(sf::RenderWindow* window);
	Player* GetPlayer() const { if (mPlayer != nullptr) { return mPlayer; } }
	const Resources& GetResources() { return mResources; }
	void AddToGameobjects(GameObject* gameobject) { mGameobjects.push_back(gameobject); }
	LLGP::Vector2f const GetRandomPosInArena();
	void RenderArenaBounds();
	bool IsGameobjectOutOfBounds(GameObject* gameobject);
	template <typename T>
	T* SpawnGameobject(sf::Texture* texture);
	void UpdateCollisions();
	sf::RenderWindow* mWindow;

	void SpawnNewEnemy();

	void UpdateArenaBounds(float dt);
	GameWorld* GetWorld() { return this; }
	void HandlePlayerDied(bool die);

	

private:
	Player* mPlayer = nullptr;
	Enemy* mEnemy = nullptr;
	FamilyMan* mFamilyMan = nullptr;
	Resources mResources;
	std::vector<GameObject*> mGameobjects;

	float mEnemySpawnTime = 5.0f;




};

template<typename T>
T* GameWorld::SpawnGameobject(sf::Texture* texture) 
{
	if (T* newGameobject = new T(this, texture)) 
	{
		mGameobjects.push_back(newGameobject);
		return newGameobject;
	}
	return nullptr;
}

